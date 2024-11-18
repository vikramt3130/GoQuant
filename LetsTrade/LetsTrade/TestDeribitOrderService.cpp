#include "OrderService.h"
#include "TestDeribitOrderService.h"
#include <string>
#include <iostream>
#include <vector>
#include <json/json.h>
#include <sstream>
#include <format> 
#include <unordered_map>
#include "JsonParser.h"
#include "CurlUtil.h"
#include "Constants.h"
#include "OrderPlaceResponseData.h"
#include "GetOpenOrdersResponseData.h"
#include "CancelOrderResponseData.h"
#include "CancelAllOrderResponseData.h"
#include "GetCurrentPositionsResponseData.h"

TestDeribitOrderService::TestDeribitOrderService()
{
	if (access_token.empty())
	{
		if (!AuthenticateAndAssignAccessToken())
		{
			std::cerr << "Failed to get AuthenticationToken ";
		}
	}
}

bool TestDeribitOrderService::AuthenticateAndAssignAccessToken()
{
	std::unordered_map<std::string, std::string> params;
	params["client_id"] = CLIENT_ID;
	params["client_secret"] = CLIENT_SECRET;
	params["grant_type"] = "client_credentials";

	std::string url = CurlUtil::BuildURL(API_AUTH, params, false);
	std::string response = CurlUtil::SendRequest(url);

	access_token = JsonParser::ParseAccessToken(response);
	return !access_token.empty();
}

bool TestDeribitOrderService::PlaceOrder(bool isBuyOrder, const std::string& instrument, int amount, const std::string& orderType, double price)
{
	std::unordered_map<std::string, std::string> params;
	params["instrument_name"] = instrument;
	params["contracts"] = std::format("{}", amount);
	params["type"] = orderType;
	if (!orderType.empty())
	{
		params["price"] = std::format("{}", price);
	}

	std::string url;

	if (isBuyOrder)
		url = CurlUtil::BuildURL(API_BUY, params);
	else
		url = CurlUtil::BuildURL(API_SELL, params);

	std::string response = CurlUtil::SendRequest(url, access_token);;

	// Extract and check order status
	const OrderPlaceResponseData& orderPlaceResponseData = JsonParser::ParseOrderPlaceResponseData(response);

	if (orderPlaceResponseData.OrderStatus == OrderPlaceResponseData::OrderStatus::Filled)
	{
		std::cout << "Order placed successfully!" << std::endl;
		std::cout << "Order ID: " << orderPlaceResponseData.OrderID << std::endl;
		std::cout << "Amount filled: " << orderPlaceResponseData.AmountFilled << std::endl;
		std::cout << "Average Price: " << orderPlaceResponseData.AveragePrice << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Order not filled. Current state: " << orderPlaceResponseData.OrderStatusEnumToString(orderPlaceResponseData.OrderStatus) << std::endl;
	}

	return false;
}

bool TestDeribitOrderService::GetOpenOrders()
{
	std::unordered_map<std::string, std::string> params;
	std::string url = CurlUtil::BuildURL(API_GET_OPEN_ORDERS, params);
	std::string response = CurlUtil::SendRequest(url, access_token);;

	// Extract and check order status
	const std::vector<GetOpenOrdersResponseData>& getOpenOrdersResponseData = JsonParser::ParseGetOpenOrdersResponseData(response);

	for(GetOpenOrdersResponseData openOrderData: getOpenOrdersResponseData)
	{		
		std::cout << "Order ID: " << openOrderData.OrderId << std::endl;
		std::cout << "Instrument Name: " << openOrderData.InstrumentName << std::endl;
		std::cout << "Amount filled: " << openOrderData.FilledAmount << std::endl;
		std::cout << "Average Price: " << openOrderData.AveragePrice << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
	}

	return getOpenOrdersResponseData.size() != 0;
}

bool TestDeribitOrderService::CancelOrder(const std::string& orderId)
{
	std::unordered_map<std::string, std::string> params;
	params["order_id"] = orderId;
	std::string url = CurlUtil::BuildURL(API_CANCEL, params);
	std::string response = CurlUtil::SendRequest(url, access_token);;

	// Extract and check order status
	CancelOrderResponseData cancelOrderIdResponseData = JsonParser::ParseCancelOrderResposeData(response);
	
	return !cancelOrderIdResponseData.OrderState.empty();
}

bool TestDeribitOrderService::CancelAllOrders()
{
	std::unordered_map<std::string, std::string> params;	
	std::string url = CurlUtil::BuildURL(API_CANCEL_ALL, params);
	std::string response = CurlUtil::SendRequest(url, access_token);;

	// Extract and check order status
	CancelAllOrdersResponseData cancelAllOrderIdResponseData = JsonParser::ParseCancelAllOrderResposeData(response);

	std::cout << "Cancelled " << cancelAllOrderIdResponseData.Result << " orders";
	return cancelAllOrderIdResponseData.Result > 0;
}

bool TestDeribitOrderService::GetCurrentPositions()
{
	std::unordered_map<std::string, std::string> params;
	std::string url = CurlUtil::BuildURL(API_GET_POSITIONS, params);
	std::string response = CurlUtil::SendRequest(url, access_token);;

	// Extract and check order status
	std::vector<GetCurrentPositionsResponseData> getCurrPosResponseDatas = JsonParser::ParseGetCurrentPositionsResponseData(response);

	for (GetCurrentPositionsResponseData currPositionResponseData : getCurrPosResponseDatas)
	{		
		std::cout << "Instrument Name: " << currPositionResponseData.InstrumentName << std::endl;
		std::cout << "Average Price: " << currPositionResponseData.AveragePrice << std::endl;
		std::cout << "Profit Loss: " << currPositionResponseData.ProfitLoss << std::endl;
		std::cout << "Direction: " << currPositionResponseData.OrderDirectionEnumToString(currPositionResponseData.OrderDirection) << std::endl;
		std::cout << "Kind: " << currPositionResponseData.KindEnumToString(currPositionResponseData.Kind) << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
	}

	return getCurrPosResponseDatas.size() != 0;
}



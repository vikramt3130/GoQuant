#include <iostream>
#include <string>
#include <vector>

#include <json/json.h>

#include "JsonParser.h"

#include "OrderPlaceResponseData.h"
#include "GetOpenOrdersResponseData.h"
#include "CancelOrderResponseData.h"
#include "CancelAllOrderResponseData.h"
#include "GetCurrentPositionsResponseData.h"

std::string JsonParser::ParseAccessToken(const std::string& response)
{
	Json::CharReaderBuilder reader;
	Json::Value json_response;
	std::istringstream response_stream(response);
	std::string errs;
	std::string access_token;
	// Parse the JSON
	if (!Json::parseFromStream(reader, response_stream, &json_response, &errs)) {
		std::cerr << "Failed to parse JSON: " << errs << std::endl;
		return "";
	}

	// Extract the access token
	if (json_response.isMember("result") && json_response["result"].isMember("access_token")) {
		access_token = json_response["result"]["access_token"].asString();
		std::cout << "Access Token: " << access_token << std::endl;
		return access_token;
	}
	else 
	{
		std::cerr << "Access token not found in response" << std::endl;
		return "";
	}
}

OrderPlaceResponseData JsonParser::ParseOrderPlaceResponseData(const std::string& response)
{	
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;
	OrderPlaceResponseData orderPlaceResponseData;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs)) 
	{
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return orderPlaceResponseData;
	}

	const Json::Value& result = jsonResponse["result"];
	if (!result.isNull()) 
	{
		const Json::Value& order = result["order"];
		orderPlaceResponseData.OrderStatus = orderPlaceResponseData.OrderStatusStringToEnum(order["order_state"].asString());
		if (orderPlaceResponseData.OrderStatus == OrderPlaceResponseData::OrderStatus::Filled)
		{
			orderPlaceResponseData.OrderID = order["order_id"].asString();
			orderPlaceResponseData.AmountFilled = order["filled_amount"].asInt();
			orderPlaceResponseData.AveragePrice = order["average_price"].asDouble();
		}		
	}

	return orderPlaceResponseData;
}

std::vector<GetOpenOrdersResponseData> JsonParser::ParseGetOpenOrdersResponseData(const std::string& response)
{	
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;
	std::vector<GetOpenOrdersResponseData> getOpenOrdersResponseData;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs))
	{
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return getOpenOrdersResponseData;
	}

	const Json::Value& results = jsonResponse["result"];
	if (!results.isNull())
	{		
		if (jsonResponse["result"].isArray())
		{
			for(const auto& result : results)
			{
				GetOpenOrdersResponseData openOrderData;
				openOrderData.InstrumentName = result["instrument_name"].asString();

				openOrderData.OrderId = result["order_id"].asString();
				openOrderData.FilledAmount = result["filled_amount"].asInt();
				openOrderData.OrderState = openOrderData.OrderStateStringToEnum(result["order_state"].asString());
				openOrderData.AveragePrice = result["average_price"].asDouble();
				openOrderData.Amount = result["amount"].asInt();
				openOrderData.Price = result["price"].asDouble();
				getOpenOrdersResponseData.push_back(openOrderData);
			}
		}		
	}

	return getOpenOrdersResponseData;
}

CancelOrderResponseData JsonParser::ParseCancelOrderResposeData(const std::string& response)
{	
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;
	CancelOrderResponseData cancelOrderResponseData;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs))
	{
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return 	cancelOrderResponseData;
		;
	}

	const Json::Value& result = jsonResponse["result"];
	if (!result.isNull())
	{		
		cancelOrderResponseData.Triggered = result["order"].asBool();
		cancelOrderResponseData.OrderState = result["order_state"].asString();
	}

	return cancelOrderResponseData;
}

CancelAllOrdersResponseData JsonParser::ParseCancelAllOrderResposeData(const std::string& response)
{
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;
	CancelAllOrdersResponseData cancelAllOrderResponseData;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs))
	{
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return 	cancelAllOrderResponseData;
		;
	}

	const Json::Value& result = jsonResponse["result"];
	if (!result.isNull())
	{
		cancelAllOrderResponseData.Result = result.asInt();		
	}

	const Json::Value& id = jsonResponse["id"];
	if (!id.isNull())
	{
		cancelAllOrderResponseData.Id = id.asInt();
	}

	return cancelAllOrderResponseData;
}

std::vector<GetCurrentPositionsResponseData> JsonParser::ParseGetCurrentPositionsResponseData(const std::string& response)
{
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;
	std::vector<GetCurrentPositionsResponseData> getOpenOrdersResponseData;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs))
	{
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return getOpenOrdersResponseData;
	}

	const Json::Value& results = jsonResponse["result"];
	if (!results.isNull())
	{
		if (jsonResponse["result"].isArray())
		{
			for (const auto& result : results)
			{
				GetCurrentPositionsResponseData getCurrPosData;
				getCurrPosData.InstrumentName = result["instrument_name"].asString();
				getCurrPosData.OrderDirection = getCurrPosData.OrderDirectionStringToEnum(result["direction"].asString());
				getCurrPosData.Kind = getCurrPosData.KindStringToEnum(result["kind"].asString());
				getCurrPosData.ProfitLoss = result["total_profit_loss"].asDouble();
				getOpenOrdersResponseData.push_back(getCurrPosData);
			}
		}
	}

	return getOpenOrdersResponseData;
}
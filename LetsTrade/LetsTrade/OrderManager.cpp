#include <string>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <format> 
#include <unordered_map>

#include "OrderManager.h"
#include "JsonParser.h"
#include "CurlUtil.h"

static const std::string API_AUTH = "auth";
static const std::string API_BUY = "buy";

bool OrderManager::AuthenticateAndAssignAccessToken() 
{	
	std::unordered_map<std::string, std::string> params;
	params["client_id"] = client_id;
	params["client_secret"] = client_secret;
	params["grant_type"] = "client_credentials";

	std::string url = CurlUtil::BuildURL(API_AUTH, params, false);
	std::string response = CurlUtil::SendRequest(url);

	access_token = JsonParser::ParseAccessToken(response);
	return !access_token.empty();
}

bool OrderManager::PlaceBuyOrder(const std::string& instrument, int amount, double price)
{	
	std::unordered_map<std::string, std::string> params;
	params["instrument_name"] = instrument;
	params["contracts"] = std::format("{}", amount);
	params["type"] = "market";

	std::string url = CurlUtil::BuildURL(API_BUY, params);
	std::string response = CurlUtil::SendRequest(url, get_access_token());;

	std::cout << "Got response" << response;
	Json::CharReaderBuilder readerBuilder;
	Json::Value jsonResponse;
	std::string errs;

	// Parse the JSON response
	std::istringstream responseStream(response);
	if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errs)) {
		std::cerr << "Failed to parse JSON response: " << errs << std::endl;
		return false;
	}

	// Extract and check order status
	const Json::Value& result = jsonResponse["result"];
	if (!result.isNull()) {
		const Json::Value& order = result["order"];
		if (order["order_state"].asString() == "filled") {
			std::cout << "Order placed successfully!" << std::endl;
			std::cout << "Order ID: " << order["order_id"].asString() << std::endl;
			std::cout << "Amount filled: " << order["filled_amount"].asInt() << std::endl;
			std::cout << "Average Price: " << order["average_price"].asDouble() << std::endl;
			return true;
		}
		else {
			std::cerr << "Order not filled. Current state: " << order["order_state"].asString() << std::endl;
		}
	}
	else {
		std::cerr << "Unexpected response format." << std::endl;
	}
	return false;
}
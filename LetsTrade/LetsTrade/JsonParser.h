#ifndef JSON_PARSER_H
#define JSON_PARSER_H

struct OrderPlaceResponseData;
struct GetOpenOrdersResponseData;
struct CancelOrderResponseData;
struct CancelAllOrdersResponseData;
struct GetCurrentPositionsResponseData;

class JsonParser
{
public:
	static std::string ParseAccessToken(const std::string& response);
	static OrderPlaceResponseData ParseOrderPlaceResponseData(const std::string& response);
	static std::vector<GetOpenOrdersResponseData> ParseGetOpenOrdersResponseData(const std::string& response);
	static CancelOrderResponseData ParseCancelOrderResposeData(const std::string& response);
	static CancelAllOrdersResponseData ParseCancelAllOrderResposeData(const std::string& response);
	static std::vector<GetCurrentPositionsResponseData> ParseGetCurrentPositionsResponseData(const std::string& response);
};
#endif // JSON_PARSER_H


#ifndef ORDER_PLACE_RESPONSEDATA_H
#define ORDER_PLACE_RESPONSEDATA_H
#include <string>
#include <unordered_map>
#include "BaseOrderData.h"

struct OrderPlaceResponseData : public BaseOrderData
{
	OrderPlaceResponseData() : OrderStatus(OrderStatus::Invalid),
		OrderID(""),
		AmountFilled(-1),
		AveragePrice(-1.0)
	{
	}

	OrderStatus OrderStatus;
	std::string OrderID;
	int AmountFilled;
	double AveragePrice;
};
#endif//ORDER_PLACE_RESPONSEDATA_H
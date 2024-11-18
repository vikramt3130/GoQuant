#ifndef GETOPENORDERSRESPONSEDATA_H
#define GETOPENORDERSRESPONSEDATA_H

#include <string>
#include "BaseOrderData.h"

struct GetOpenOrdersResponseData : public BaseOrderData
{
	GetOpenOrdersResponseData() : InstrumentName(""),
		OrderId(""),
		FilledAmount(-1),
		OrderState(OrderState::Invalid),
		AveragePrice(-1.0),
		Amount(-1),
		Price(-1.0)
	{
	}

	std::string InstrumentName;
	std::string OrderId;
	int FilledAmount;
	OrderState OrderState;
	double AveragePrice;
	int Amount;
	double Price;
};
#endif//GETOPENORDERSRESPONSEDATA_H
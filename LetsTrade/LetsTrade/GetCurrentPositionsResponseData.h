#ifndef GETCURRENTPOSITIONSRESPONSEDATA_H
#define GETCURRENTPOSITIONSRESPONSEDATA_H

#include <string>
#include "BaseOrderData.h"

struct GetCurrentPositionsResponseData : public BaseOrderData
{
	GetCurrentPositionsResponseData() : InstrumentName(""), 
		AveragePrice(0.0),
		OrderDirection(OrderDirection::Invalid),
		Kind(Kind::Invalid),
		ProfitLoss(0.0)
	{
	}	

	double AveragePrice;
	OrderDirection OrderDirection;
	std::string InstrumentName;
	Kind Kind;
	double ProfitLoss;
};
#endif//GETCURRENTPOSITIONSRESPONSEDATA_H
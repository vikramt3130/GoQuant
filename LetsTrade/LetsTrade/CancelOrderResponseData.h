#ifndef CANCELORDERIDRESPONSEDATA_H
#define CANCELORDERIDRESPONSEDATA_H

#include <string>
#include "BaseOrderData.h"

struct CancelOrderResponseData : public BaseOrderData
{
	CancelOrderResponseData() : Triggered(false), OrderState("")
	{
	}

	bool Triggered;
	std::string OrderState;
};
#endif//CANCELORDERIDRESPONSEDATA_H
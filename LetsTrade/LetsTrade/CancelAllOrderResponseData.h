#ifndef CANCELALLORDERIDRESPONSEDATA_H
#define CANCELALLORDERIDRESPONSEDATA_H

#include <string>
#include "BaseOrderData.h"

struct CancelAllOrdersResponseData : public BaseOrderData
{
	CancelAllOrdersResponseData() : Id(0), Result(0)
	{
	}

	int Id;
	int Result;
};
#endif//
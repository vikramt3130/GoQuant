#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H
#include <string>

class OrderService
{
public:
	virtual bool AuthenticateAndAssignAccessToken() = 0;
	virtual bool PlaceOrder(bool isBuyOrder, const std::string& instrument, int amount, const std::string& orderType = "", double price = 0.0) = 0;
	virtual bool GetOpenOrders() = 0;
	virtual bool CancelOrder(const std::string& orderId) = 0;
	virtual bool CancelAllOrders() = 0;
	virtual bool GetCurrentPositions() = 0;
};
#endif//ORDERSERVICE_H


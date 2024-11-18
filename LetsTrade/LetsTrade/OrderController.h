#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H
class OrderService;

class OrderController
{
public:
	OrderController(OrderService* orderService) :m_pOrderService(orderService) {};
	~OrderController();

	bool PlaceOrder(bool isBuyOrder, const std::string& instrument, int amount, const std::string& orderType = "", double price = 0.0);
	bool GetOpenOrders();
	bool CancelOrder(const std::string& orderId);
	bool CancelAllOrder();
	bool GetCurrentPositions();

private:
	OrderService* m_pOrderService = nullptr;
};
#endif//ORDERCONTROLLER_H

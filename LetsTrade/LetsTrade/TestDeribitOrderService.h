#ifndef TEST_DERIBIT_ORDER_SERVICE_H
#define TEST_DERIBIT_ORDER_SERVICE_H
class TestDeribitOrderService : public OrderService
{
public:
	TestDeribitOrderService();
	// Inherited via OrderService
	bool PlaceOrder(bool isBuyOrder, const std::string& instrument, int amount, const std::string& orderType = "", double price = 0.0) override;
	bool AuthenticateAndAssignAccessToken() override;
	bool GetOpenOrders() override;
	bool CancelOrder(const std::string& orderId) override;
	bool CancelAllOrders() override;
	bool GetCurrentPositions() override;

private:
	std::string client_id;
	std::string client_secret;
	std::string access_token;
};
#endif//TEST_DERIBIT_ORDER_SERVICE_H


#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

class OrderController;

class MenuController
{
public:
	MenuController();
	~MenuController();
	void StartMenuLoop();

private:
	void DisplayMenu();
	void PlaceOrder();
	void CancelOrder();
	bool ValidateOrder(const std::string& input) const;

	OrderController* m_pOrderController;
};
#endif//ORDERCONTROLLER_H

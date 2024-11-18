#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>

#include "MenuController.h"
#include "OrderController.h"
#include "OrderService.h"
#include "TestDeribitOrderService.h"

static bool IsPositiveInteger(const std::string& str) 
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

static bool IsPositiveDouble(const std::string& str) 
{
	try 
	{
		double value = std::stod(str);
		return value > 0;
	}
	catch (...) 
	{
		return false;
	}
}

MenuController::MenuController():m_pOrderController(new OrderController(new TestDeribitOrderService()))
{

}

MenuController::~MenuController()
{
	if (m_pOrderController != nullptr)
	{
		delete m_pOrderController;
		m_pOrderController = nullptr;
	}
}

void MenuController::StartMenuLoop()
{
	int choice = 0;
	while (true)
	{
		DisplayMenu();
		std::cout << "Please select an option: "<< std::endl;
		std::cin >> choice;

		if (std::cin.fail()) 
		{
			std::cin.clear();  // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
			std::cout << "Invalid input. Please enter a number between 1 and 6" << std::endl;;
			continue;  // Restart the loop to display the menu again
		}

		if (choice < 1 || choice > 6) 
		{
			std::cout << "Please enter a valid option (1-6)" << std::endl;;
			continue;  // Restart the loop to display the menu again
		}

		switch (choice)
		{
		case 1:
			PlaceOrder();
			break;
		case 2:
			std::cout << "Cancelling Order..." << std::endl;
			CancelOrder();
			break;
		case 3:
			std::cout << "Cancelling All Order..." << std::endl;
			m_pOrderController->CancelAllOrder();
			break;		
		case 4:
			std::cout << "Getting Orderbook..." << std::endl;
			m_pOrderController->GetOpenOrders();
			// Call the method to get orderbook here
			break;
		case 5:
			std::cout << "Viewing Current Positions..." << std::endl;
			m_pOrderController->GetCurrentPositions();
			break;
		case 6:
			std::cout << "Exiting..." << std::endl;
			return;  // Exit the loop and the function
		default:
			std::cout << "Invalid choice. Please select a number between 1 and 6." << std::endl;
			break;
		}

		// Clear input buffer after each loop
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
void MenuController::DisplayMenu()
{
	std::cout << std::endl;
	std::cout << "1. Place Order" << std::endl;
	std::cout << "2. Cancel Order" << std::endl;
	std::cout << "3. Cancel All Order" << std::endl;
	std::cout << "4. Get Orderbook" << std::endl;
	std::cout << "5. View Current Positions" << std::endl;
	std::cout << "6. Exit" << std::endl;
}

void MenuController::PlaceOrder()
{
	std::cout << "Enter order details in following format:" << std::endl;
	std::cout << "<Buy/Sell> <Symbol> <Amount> <Market/limit> <price>\nPlease enter 0.0 price for market order" << std::endl;
	std::cout << "For Example: \nbuy ETH-PERPETUAL 1 limit 2000.5\nsell ETH-PERPETUAL 1 market 0.0" << std::endl;
	std::string input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
	std::getline (std::cin, input);

	if (ValidateOrder(input))
	{		
		std::istringstream iss(input);
		std::string action, symbol, orderType;
		int amount;
		double price;
		bool IsBuyOrder = false;
		iss >> action >> symbol >> amount >> orderType >> price;
			
		if (action == "buy")
		{
			IsBuyOrder = true;
		}

		if (m_pOrderController->PlaceOrder(IsBuyOrder, symbol, amount, orderType, price))
		{
			std::cout << "Successfully placed " << orderType << " order for " << symbol << std::endl;
		}
		else
		{
			std::cerr << "Failed to placed " << orderType << " order for " << symbol << std::endl;
		}
	}
	else
	{
		std::cerr << "Wrong Input!!! Please refer example to place valid order."<< std::endl;
	}
}
void MenuController::CancelOrder()
{
	std::cout << "The the orderId to cancel(can be viewed through orderbook):" << std::endl;	
	std::string input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
	std::cin >> input;	

	m_pOrderController->CancelOrder(input);
}

bool MenuController::ValidateOrder(const std::string& input) const
{
	std::istringstream iss(input);
	std::vector<std::string> parts;
	std::string part;

	// Split the input by whitespace
	while (iss >> part) 
	{
		parts.push_back(part);
	}

	if (parts.size() != 5) 
		return false; // Ensure 5 parts

	// Validate Order Direction
	if (parts[0] != "buy" && parts[0] != "sell") 
		return false;

	// Validate Symbol (non-empty)
	if (parts[1].empty()) 
		return false;

	// Validate Amount (positive integer)
	if (!IsPositiveInteger(parts[2]))
		return false;

	// Validate Order Type
	if (parts[3] != "market" && parts[3] != "limit") 
		return false;

	// Validate Price if Order Type is "Limit"
	if (parts[3] == "limit" && !IsPositiveDouble(parts[4])) 
		return false;

	return true;
}

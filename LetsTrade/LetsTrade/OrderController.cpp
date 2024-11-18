#include <string>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <format> 
#include <unordered_map>

#include "OrderController.h"
#include "JsonParser.h"
#include "CurlUtil.h"
#include "OrderService.h"

OrderController::~OrderController()
{
	if (m_pOrderService != nullptr)
	{
		delete m_pOrderService;
		m_pOrderService = nullptr;
	}
}

bool OrderController::PlaceOrder(bool isBuyOrder, const std::string& instrument, int amount, const std::string& orderType, double price)
{
	return m_pOrderService->PlaceOrder(isBuyOrder, instrument, amount, orderType, price);
}

bool OrderController::GetOpenOrders()
{
	return m_pOrderService->GetOpenOrders();
}

bool OrderController::CancelOrder(const std::string& orderId)
{
	return m_pOrderService->CancelOrder(orderId);
}

bool OrderController::CancelAllOrder()
{
	return m_pOrderService->CancelAllOrders();
}

bool OrderController::GetCurrentPositions()
{
	return m_pOrderService->GetCurrentPositions();
}
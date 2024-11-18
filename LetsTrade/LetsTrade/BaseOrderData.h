#ifndef BASEORDERDATA_H
#define BASEORDERDATA_H
struct BaseOrderData
{
	enum class OrderDirection
	{
		Invalid = 0,
		Buy,
		Sell
	};

	enum class OrderState
	{
		Invalid = 0,
		Open,
		Close
	};

	enum class OrderStatus
	{
		Invalid = 0,
		Filled,
		Unfilled,
		Partial,
		Failed
	};

	enum class Kind
	{
		Invalid = 0,
		Future,
		Spot,
		Options
	};

	std::string OrderStatusEnumToString(OrderStatus eOrderStatus) const
	{
		switch (eOrderStatus)
		{
		case OrderStatus::Invalid:
			return "invalid";
			break;
		case OrderStatus::Filled:
			return "filled";
			break;
		case OrderStatus::Unfilled:
			return "unfilled";
			break;
		case OrderStatus::Partial:
			return "partial";
			break;
		case OrderStatus::Failed:
			return "failed";
			break;
		default: return "";
		}
	}

	OrderStatus OrderStatusStringToEnum(const std::string& strOrderStatus) const
	{
		if (strOrderStatus == "invalid")
			return OrderStatus::Invalid;
		else if (strOrderStatus == "filled")
			return OrderStatus::Filled;
		else if (strOrderStatus == "unfilled")
			return OrderStatus::Unfilled;
		else if (strOrderStatus == "partial")
			return OrderStatus::Partial;
		else if (strOrderStatus == "failed")
			return OrderStatus::Failed;
		else
			return OrderStatus::Invalid;
	}

	std::string OrderDirectionEnumToString(OrderDirection eOrderDirection) const
	{
		switch (eOrderDirection)
		{
		case OrderDirection::Invalid:
			return "invalid";
			break;
		case OrderDirection::Buy:
			return "buy";
			break;
		case OrderDirection::Sell:
			return "sell";
			break;
		default: return "";
		}
	}

	OrderDirection OrderDirectionStringToEnum(const std::string& strOrderDirection) const
	{
		if (strOrderDirection == "invalid")
			return OrderDirection::Invalid;
		else if (strOrderDirection == "buy")
			return OrderDirection::Buy;
		else if (strOrderDirection == "sell")
			return OrderDirection::Sell;
		else
			return OrderDirection::Invalid;
	}

	std::string OrderStateEnumToString(OrderState eOrderState) const
	{
		switch (eOrderState)
		{
		case OrderState::Invalid:
			return "invalid";
			break;
		case OrderState::Open:
			return "open";
			break;
		case OrderState::Close:
			return "close";
			break;
		default: return "";
		}
	}

	OrderState OrderStateStringToEnum(const std::string& strOrderState) const
	{
		if (strOrderState == "invalid")
			return OrderState::Invalid;
		else if (strOrderState == "open")
			return OrderState::Open;
		else if (strOrderState == "close")
			return OrderState::Close;
		else
			return OrderState::Invalid;
	}

	Kind KindStringToEnum(const std::string& strKind) const
	{
		if (strKind == "invalid")
			return Kind::Invalid;
		else if (strKind == "spot")
			return Kind::Spot;
		else if (strKind == "future")
			return Kind::Future;
		else if (strKind == "options")
			return Kind::Options;
		else
			return Kind::Invalid;
	}

	std::string KindEnumToString(Kind eKind) const
	{
		switch (eKind)
		{
		case Kind::Invalid:
			return "invalid";
			break;
		case Kind::Spot:
			return "spot";
			break;
		case Kind::Future:
			return "future";
			break;
		case Kind::Options:
			return "options";
			break;
		default: return "";
		}
	}
};
#endif//BASEORDERDATA_H
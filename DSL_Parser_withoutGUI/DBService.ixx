module;

export module DBService;
import std;
import DataAccessObject;

//interface

export std::string dispatchService(std::string_view serviceName, std::string_view methodName,const std::vector<std::string>& args);
class OrderService
{
public:
	std::string getStatus(std::string_view orderID);
	std::string applyRefund(std::string_view orderID, std::string_view reason);
	
private:
	OrderDAO orderDAO;
};

class UserService
{
public:
	std::string getName(std::string_view userID);

private:
	UserDAO userDAO;
};

class InventoryService
{
public:
	std::string getStock(std::string_view productID);

private:
	InventoryDAO inventoryDAO;
};

class CouponService
{
public:
	std::string apply(std::string_view couponCode, std::string_view userID);

private:
	CouponDAO couponDAO;
};

class PromotionService
{
public:
	std::string getTodayPromo();

private:
	PromotionDAO promotionDAO;
};

//implementations

export std::string dispatchService(std::string_view serviceName, std::string_view methodName,const std::vector<std::string>& args)
{
	static OrderService orderServ;
	static UserService userServ;
	static InventoryService inventoryServ;
	static CouponService couponServ;
	static PromotionService promotionServ;

	if (serviceName == "OrderService") {
		if (methodName == "getStatus") {
			std::string result{ orderServ.getStatus(args[0]) };
			return result;
		}
		else if (methodName == "applyRefund") {
			std::string result{ orderServ.applyRefund(args[0],args[1])};
			return result;
		}
	}
	else if (serviceName == "UserService") {
		if (methodName == "getName") {
			std::string result{ userServ.getName(args[0])};
			return result;
		}
	}
	else if (serviceName == "InventoryService") {
		if (methodName == "getStock") {
			return inventoryServ.getStock(args[0]);
		}
	}
	else if (serviceName == "CouponService") {
		if (methodName == "apply") {
			return couponServ.apply(args[0], args[1]);
		}
	}
	else if (serviceName == "PromotionService") {
		if (methodName == "getTodayPromo") {
			return promotionServ.getTodayPromo();
		}
	}
	return "";
}

std::string OrderService::getStatus(std::string_view orderID)
{
	return orderDAO.getStatus(orderID);
}
std::string OrderService::applyRefund(std::string_view orderID,std::string_view reason)
{
	return orderDAO.applyRefund(orderID,reason);
}

std::string UserService::getName(std::string_view userID)
{
	return userDAO.getName(userID);
}

std::string InventoryService::getStock(std::string_view productID)
{
	return inventoryDAO.getStock(productID);
}

std::string CouponService::apply(std::string_view couponCode, std::string_view userID)
{
	return couponDAO.apply(couponCode, userID);
}

std::string PromotionService::getTodayPromo()
{
	return promotionDAO.getTodayPromo();
}
module;

export module DataAccessObject;
import std;

//interface
unsigned long long polyHash(const std::string& s, int max);

export class OrderDAO
{
public:
	std::string getStatus(std::string_view orderID);
	std::string applyRefund(std::string_view orderID, std::string_view reason);
};

export class UserDAO
{
public:
	std::string getName(std::string_view userID);
};

export class InventoryDAO
{
public:
	std::string getStock(std::string_view productID);
};

export class CouponDAO
{
public:
	std::string apply(std::string_view couponCode, std::string_view userID);
};

export class PromotionDAO
{
public:
	std::string getTodayPromo();
};

//implementations

unsigned long long polyHash(const std::string& s, int max) {
	const unsigned long long base = 131;
	unsigned long long hash = 0;
	for (char c : s) {
		hash = hash * base + static_cast<unsigned long long>(c);
	}
	return hash % max;
}

std::string OrderDAO::getStatus(std::string_view orderID)
{
	//std::cout << "orderid:" << orderID<<"\n";

	int orderIDInt{ std::stoi(std::string(orderID)) };
	switch(orderIDInt % 3) {
	case 0:
		return "SHIPPED";
		break;
	case 1:
		return "DELIVERED";
		break;
	case 2:
		return "NONE";
		break;
	}
}
std::string OrderDAO::applyRefund(std::string_view orderID, std::string_view reason)
{
	//std::cout << "orderid:" << orderID << "\n";

	int orderIDInt{ std::stoi(std::string(orderID)) };
	switch (orderIDInt % 2) {
	case 0:
		return "SUCCESS";
		break;
	case 1:
		return "Fail";
		break;
	}
}

std::string UserDAO::getName(std::string_view userID)
{
	return "user_"+std::string(userID);
}

std::string InventoryDAO::getStock(std::string_view productID)
{
	return std::to_string(polyHash(std::string(productID), 10000) - 5000);
}

std::string CouponDAO::apply(std::string_view couponCode, std::string_view userID)
{
	int couponCodeInt{ std::stoi(std::string(couponCode)) };
	switch (couponCodeInt % 3) {
	case 0:
		return "VALID";
		break;
	case 1:
		return "EXPIRED";
		break;
	case 2:
		return "INVALID";
		break;
	}
}

std::string PromotionDAO::getTodayPromo()
{
	auto now = std::chrono::system_clock::now();
	std::string time = std::format("{:%Y-%m-%d %H:%M:%S}", now);
	switch (polyHash(std::string(time),3) ) {
	case 0:
		return "满100减20";
		break;
	case 1:
		return "满100减30";
		break;
	case 2:
		return "NONE";
		break;
	}

}


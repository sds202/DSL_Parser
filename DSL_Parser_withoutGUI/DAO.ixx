module;

export module DataAccessObject;
import std;

//interface

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

//implementations

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
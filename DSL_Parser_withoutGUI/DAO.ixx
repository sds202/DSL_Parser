module;

export module DataAccessObject;
import std;

export class OrderDAO
{
public:
	std::string getStatus(std::string_view orderID);
	std::string applyRefund(std::string_view orderID, std::string_view reason);
};


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
		return "?";
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
export module DBService;
import DataAccessObject;
import Context;
import std;

export std::string dispatchService(std::string_view serviceName, std::string_view methodName,const std::vector<std::string>& args);

class OrderService
{
public:
	std::string getStatus(std::string_view orderID);
	std::string applyRefund(std::string_view orderID, std::string_view reason);
	
private:
	OrderDAO DAO;
};

std::string OrderService::getStatus(std::string_view orderID)
{
	return DAO.getStatus(orderID);
}
std::string OrderService::applyRefund(std::string_view orderID,std::string_view reason)
{
	return DAO.applyRefund(orderID,reason);
}

export std::string dispatchService(std::string_view serviceName, std::string_view methodName,const std::vector<std::string>& args)
{
	static OrderService orderServ;

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
}
module;
#include<drogon/drogon.h>

export module SessionManager;
import std;
import Context;

export struct UserSession {
	std::mutex mtx;
	Context ctx;
	std::string lastTimeIntent;
	std::set<std::string> missingSlot;
	size_t currentDslVersion{ 0 };
};

export class SessionManager
{
public:
	SessionManager():sessions(drogon::app().getLoop(),1.0,3,60){ }
	std::shared_ptr<UserSession> getOrCreateUserSession(const std::string & userId);
private:
	drogon::CacheMap<std::string, std::shared_ptr<UserSession>> sessions;
	//std::map<std::string, std::shared_ptr<UserSession>> sessions;
	//std::shared_mutex session_mtx;
};

//implementations

std::shared_ptr<UserSession> SessionManager::getOrCreateUserSession(const std::string& userId)
{
	std::shared_ptr<UserSession> session;

	if (sessions.findAndFetch(userId,session)) {
		return session;
	}
	else {
		session = std::make_shared<UserSession>();
		session->ctx.add("user_id", userId);

		sessions.insert(userId, session,600);
	}
	return session;
}


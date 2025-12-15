export module SessionManager;
import std;
import Context;

export struct UserSession {
	std::mutex mtx;
	Context ctx;
	std::string lastTimeIntent;
	std::set<std::string> missingSlot;
};

export class SessionManager
{
public:
	std::shared_ptr<UserSession> getOrCreateUserSession(const std::string & userId);
private:
	std::map<std::string, std::shared_ptr<UserSession>> sessions;
	std::shared_mutex session_mtx;
};

//implementations

std::shared_ptr<UserSession> SessionManager::getOrCreateUserSession(const std::string& userId)
{
	std::shared_ptr<UserSession> session;
	{
		std::shared_lock<std::shared_mutex> session_lock(session_mtx);
		auto it{ sessions.find(userId) };
		if (it != sessions.end()) {
			session = it->second;
		}
	}
	if (!session) {
		std::unique_lock<std::shared_mutex>session_write_lock(session_mtx);
		auto it = sessions.find(userId);
		if (it == sessions.end()) {
			session = std::make_shared<UserSession>();
			session->ctx.add("user_id", userId);
			sessions[userId] = session;
		}
		else {
			session = it->second;
		}
	}

	return session;
}

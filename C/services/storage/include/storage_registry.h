#ifndef _STORAGE_REGISTRY_H
#define _STORAGE_REGISTRY_H

#include <vector>
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>

typedef std::vector<std::pair<std::string *, std::string *> > REGISTRY;

class StorageRegistry {
	public:
		StorageRegistry();
		~StorageRegistry();
		void		registerAsset(const std::string& asset, const std::string& url);
		void		unregisterAsset(const std::string& asset, const std::string& url);
		void		process(const std::string& payload);
		void		run();
	private:
		void		processPayload(char *payload);
		void		sendPayload(const std::string& url, char *payload);
		REGISTRY			m_registrations;
		std::queue<char *>		m_queue;
		std::mutex			m_qMutex;
		std::thread			*m_thread;
		std::condition_variable		m_cv;
		std::mutex			m_cvMutex;
		bool				m_running;
};

#endif

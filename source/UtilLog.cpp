#include "UtilLog.h"
#include <memory>
#include <mutex>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace Util;

static Log* _LogInstance;

void Log::init(const char* logFilePath) {
	_LogInstance = new Log(logFilePath);
}

Log::Log (const char* logFilePath) {
	assert(_LogInstance == nullptr);
	//if(_LogInstance != nullptr) 
	//	std::cout << "_this != nullptr" << std::endl;

	pthread_mutex_init(&log_mutex, nullptr);
	pthread_cond_init(&log_cond, nullptr);
	if(logFilePath == nullptr) {
		//打开当前活动目录的日志文件
		std::string fileName;
		std::stringstream ss;
		ss << "logfile-" << boost::gregorian::day_clock::local_day() << ".txt";
		ss >> fileName;
		fp = ::fopen(fileName.c_str(), "a+");

	} else {
		//打开logFilePath的文件
		fp = ::fopen(logFilePath, "a+");
	}
	if(fp == NULL) 
		std::cerr << "日志文件打开失败" << std::endl;
}

Log::~Log() {
	if(fp != nullptr)
		::fclose(fp);
}

Log* Log::getIntences() {
	if(_LogInstance == nullptr) 
	{
		std::cerr << "日志线程未启动" << std::endl;
		assert(_LogInstance != nullptr);
	}
	return _LogInstance;

}

pid_t Log::InitLogThread(const char* logFilePath) {
	pthread_t pt;
	init(logFilePath);
	pthread_create(&pt, NULL, Log::LogThreadCallBack, (void*)getIntences());
	//pthread_detach(pt);
	return pt;
}


void* Log::LogThreadCallBack(void *arg) {
	Log& logObj = *((Log*)arg);

	log(Log::INFO, "日志线程启动...");
	while(true)
	{
		pthread_mutex_lock(&(logObj.log_mutex));
		::timespec t;
		::timeval now;
		::gettimeofday(&now, nullptr);
		t.tv_sec = now.tv_sec + 3;
		t.tv_nsec = now.tv_usec * 1000;
		pthread_cond_timedwait(&(logObj.log_cond), &(logObj.log_mutex),  &t);
		//std::cout << "writting..." << std::endl;

		//可以优化为写时拷贝
		for(auto& i : logObj.Error) 
			fprintf(logObj.fp, "%s\n", i.c_str());
		logObj.Error.clear();

		for(auto& i : logObj.Warning) 
			fprintf(logObj.fp, "%s\n", i.c_str());
		logObj.Warning.clear();

		for(auto& i : logObj.Debug) 
			fprintf(logObj.fp, "%s\n", i.c_str());
		logObj.Debug.clear();

		for(auto& i : logObj.Info) 
			fprintf(logObj.fp, "%s\n", i.c_str());
		logObj.Info.clear();

		pthread_mutex_unlock(&(logObj.log_mutex));

	}
	return nullptr;

}


void Log::log(RANK rank, std::string& msg) {
	Log* obj = getIntences();
	time_t now = time(nullptr);
	strftime(obj->m_LogTime, 32, "%Y-%m-%d %H:%M:%S : ", localtime(&now));
	std::string s(obj->m_LogTime);
	switch (rank) {
		case INFO:
			s += "INFO : ";
			s += msg;
			obj->Info.push_back(s);
			if(obj->Info.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case DEBUG:
			s += "DEBUG : ";
			s += msg;
			obj->Debug.push_back(s);
			if(obj->Debug.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case WARNING:
			s += "WARNING : ";
			s += msg;
			obj->Warning.push_back(s);
			if(obj->Warning.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case ERROR:
			s += "ERROR : ";
			s += msg;
			obj->Error.push_back(s);
			pthread_cond_signal(&(obj->log_cond));
			break;
		default:
			return ;
	}

}

void Log::log(RANK rank, const char* msg) {
	Log* obj = getIntences();
	time_t now = time(nullptr);
	strftime(obj->m_LogTime, 32, "%Y-%m-%d %H:%M:%S : ", localtime(&now));
	std::string s(obj->m_LogTime);
	switch (rank) {
		case INFO:
			s += "INFO : ";
			s += msg;
			obj->Info.push_back(s);
			if(obj->Info.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case DEBUG:
			s += "DEBUG : ";
			s += msg;
			obj->Debug.push_back(s);
			if(obj->Debug.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case WARNING:
			s += "WARNING : ";
			s += msg;
			obj->Warning.push_back(s);
			if(obj->Warning.size() > 10) ::pthread_cond_signal(&(obj->log_cond));
			break;
		case ERROR:
			s += "ERROR : ";
			s += msg;
			obj->Error.push_back(s);
			pthread_cond_signal(&(obj->log_cond));
			break;
		default:
			return ;
	}

}

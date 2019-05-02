#include <memory>
#include <mutex>
#include <assert.h>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "Log.h"


static Log* _LogInstance = nullptr;

void Log::init(const char* logFilePath) {
	_LogInstance = new Log(logFilePath);
}

Log::Log (const char* logFilePath) {
	if(_LogInstance != nullptr) 
	{
		std::cout << "logfile != nullptr" << std::endl;
		exit(-1);
	}

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

pthread_t Log::InitLogThread(const char* logFilePath) {
	pthread_t pt;
	init(logFilePath);
	pthread_create(&pt, NULL, Log::LogThreadCallBack, (void*)getIntences());
	//pthread_detach(pt);
	return pt;
}

void Log::writeInLogFile() {
	pthread_mutex_lock(&log_mutex);
	::timespec t;
	::timeval now;
	::gettimeofday(&now, nullptr);
	t.tv_sec = now.tv_sec + 3;
	t.tv_nsec = now.tv_usec * 1000;
	pthread_cond_timedwait(&log_cond, &log_mutex,  &t);
	//std::cout << "writting..." << std::endl;

	//可以优化为写时拷贝
	for(auto& i : Error) 
		fprintf(fp, "%s\n", i.c_str());
	Error.clear();
	::fflush(fp);

	for(auto& i : Warning) 
		fprintf(fp, "%s\n", i.c_str());
	Warning.clear();

	for(auto& i : Debug) 
		fprintf(fp, "%s\n", i.c_str());
	Debug.clear();

	for(auto& i : Info) 
		fprintf(fp, "%s\n", i.c_str());
	Info.clear();

	pthread_mutex_unlock(&(log_mutex));

}


void* Log::LogThreadCallBack(void *arg) {
	log(Log::INFO, "日志线程启动...");
	while(true) {
		((Log*)arg)->writeInLogFile();
	}
	return nullptr;

}

void Log::addLog(RANK rank, const std::string logMsg) {

	pthread_mutex_lock(&log_mutex);
	switch (rank) {
		case INFO:
			Info.push_back(logMsg);
			if(Info.size() > 10) ::pthread_cond_signal(&log_cond);
			break;
		case DEBUG:
			Debug.push_back(logMsg);
			if(Debug.size() > 10) ::pthread_cond_signal(&log_cond);
			break;
		case WARNING:
			Warning.push_back(logMsg);
			if(Warning.size() > 10) ::pthread_cond_signal(&log_cond);
			break;
		case ERROR:
			Error.push_back(logMsg);
			pthread_cond_signal(&log_cond);
			break;
		default:
			return ;
	}
	pthread_mutex_unlock(&log_mutex);
}

void Log::log(RANK rank, std::string& msg) {
	char logTime[32];
	time_t now = time(nullptr);
	strftime(logTime, 32, "%Y-%m-%d %H:%M:%S : ", localtime(&now));
	std::string s(logTime);
	switch (rank) {
		case INFO:
			s += "INFO : ";
			s += msg;
			break;
		case DEBUG:
			s += "DEBUG : ";
			s += msg;
			break;
		case WARNING:
			s += "WARNING : ";
			s += msg;
			break;
		case ERROR:
			s += "ERROR : ";
			s += msg;
			break;
		default:
			return ;
	}

	Log* obj = getIntences();
	obj->addLog(rank, s);

}

void Log::log(RANK rank, const char* msg) {
	time_t now = time(nullptr);
	char logTime[32];
	strftime(logTime, 32, "%Y-%m-%d %H:%M:%S : ", localtime(&now));
	std::string s(logTime);
	switch (rank) {
		case INFO:
			s += "INFO : ";
			s += msg;
			break;
		case DEBUG:
			s += "DEBUG : ";
			s += msg;
			break;
		case WARNING:
			s += "WARNING : ";
			s += msg;
			break;
		case ERROR:
			s += "ERROR : ";
			s += msg;
			break;
		default:
			return ;
	}

	Log* obj = getIntences();
	obj->addLog(rank, s);

}

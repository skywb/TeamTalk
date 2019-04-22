#include <cassert>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <boost/date_time/gregorian/gregorian.hpp>


#include "Util.h"
namespace  Util {
	class Log
	{
	public:
		virtual ~Log ();
	
		static Log* getIntences();
		static pthread_t InitLogThread(const char* logFilePath);


		enum RANK {
			INFO = 1,
			DEBUG = 2,
			WARNING = 3,
			ERROR = 4
		};



		static void log(RANK rank, std::string& msg);
		static void log(RANK rank, const char* msg);

		static void* LogThreadCallBack(void *);

		void addLog(RANK rank, const std::string logMsg);
		void writeInLogFile();
	private:
		Log (const char* logFilePath);

		static void init(const char* logFilePath);
		
		FILE* fp;
		pthread_mutex_t log_mutex;
		pthread_cond_t log_cond;

		std::vector<std::string> Info;
		std::vector<std::string> Debug;
		std::vector<std::string> Warning;
		std::vector<std::string> Error;
	};



}

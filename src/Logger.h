#pragma once

#include "Log.h"

namespace Hydra
{
    class Logger
	{
	public:
		friend class Log;
	    void log(string message = "Default log output", logFlag flag = hydsys, string name = "sysLog"); //!< Logs something in the logger of the given name
	    void newLog(string name = "sysLog", string filename = "sysLog"); //!< Creates a new log with the specified name and filename
	    Log* getLog(string name); //!< Returns a pointer to the log with the specified name.
	    void flushLogBuffers(); //!< Manually flushes all log buffers.
		static Logger* getInstance();
	private:
		static Logger* instance;
		vector<Log> logFiles;
		Logger();
		~Logger();
	};
};

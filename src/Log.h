#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <sstream>
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;

namespace Hydra
{
    #define MAX_LOGBUFFER_ENTRIES 15

    enum logFlag {error, hydsys, info, resource};
    class Log
	{
    public:
	    Log(string newName, string newFilename);
	    void log(string message, logFlag flag = hydsys); //!< Writes a message (with timestamp) to the log with the specified flag
	    void flushBuffer();
	private:
	    vector<string> logBuffer;
        string filename;
		string name;
		friend class Logger;
	};
}

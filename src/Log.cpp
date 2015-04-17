#include "Log.h"

namespace Hydra
{
    Log::Log(string newName, string newFilename)
    {
        name = newName;
        filename = newFilename + ".txt";
        log("Init creation of logfile " + filename);
    }
    void Log::log(string message, logFlag flag)
    {
        //Output time for logging purposes
        time_t rawTime;
        tm* timeInfo;
        time(&rawTime);
        timeInfo = localtime(&rawTime);

        string flagText;
        switch (flag)
        {
        case error:
            flagText = "[ERROR]\t\t";
            break;
        case info:
            flagText = "[INFO]\t\t";
            break;
        case resource:
            flagText = "[RESOURCE]\t";
            break;
        case hydsys:
            flagText = "[SYSTEM]\t";
            break;
        default:
            flagText = "[NOFLAG]\t";
            break;
        }

        stringstream logEntry;
        logEntry << "[" << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << "]\t";
        logEntry << flagText;
        logEntry << message;
        logBuffer.push_back(logEntry.str());
        if (logBuffer.size() >= MAX_LOGBUFFER_ENTRIES)
            flushBuffer();
    }
    void Log::flushBuffer()
    {
        //TODO: Have this operate in a separate thread (for efficiency)
        ofstream file;
        file.open(filename);
        for (auto iter = logBuffer.begin(); iter != logBuffer.end(); iter++)
            file << *iter << endl;
    }
}

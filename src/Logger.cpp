#include "Logger.h"

namespace Hydra
{
    Logger* Logger::instance = NULL;
    Logger* Logger::getInstance()
    {
        if (instance == NULL)
            instance = new Logger;
        return instance;
    }
    Logger::Logger()
    {
        newLog("sysLog", "sysLog");
    }
    Logger::~Logger() {}
    void Logger::log(string message, logFlag flag, string name)
    {
        //Find the correct log, then log the message with it
        for (auto iter = logFiles.begin(); iter != logFiles.end(); iter++)
        {
            if (iter->name == name)
            {
                iter->log(message, flag);
                return;
            }
        }
        //At this point, it is confirmed that no log file exists.
        log("Cannot find log " + name + ", creating new one at." + name + ".txt", info);
        Log newLog(name, name);
        newLog.log(message, flag);
        logFiles.push_back(newLog);
    }
    void Logger::newLog(string name, string filename)
    {
        //Check for duplicate logs
        for (auto iter = logFiles.begin(); iter != logFiles.end(); iter++)
        {
            if (iter->name == name)
                return; //Duplicate log found.
        }
        Log _newLog(name, filename);
        logFiles.push_back(_newLog);
    }
    Log* Logger::getLog(string name)
    {
        for (auto iter = logFiles.begin(); iter != logFiles.end(); iter++)
        {
            if (iter->name == name)
                return &(*iter);
        }
        return NULL;
    }
    void Logger::flushLogBuffers()
    {
        for (auto iter = logFiles.begin(); iter != logFiles.end(); iter++)
            iter->flushBuffer();
    }
};

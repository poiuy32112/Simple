#include "Logger.h"
#include <iostream>
#include <ctime>

std::ofstream Logger::logFile;
bool Logger::isInitialized = false;

void Logger::Init(const std::string& filename)
{
    if (!isInitialized)
    {
        logFile.open(filename, std::ios::out | std::ios::app);
        isInitialized = true;
        Info("日志系统初始化成功");
    }
}

void Logger::Log(Level level, const std::string& message)
{
    if (!isInitialized)
    {
        Init();
    }

    // 获取当前时间
    time_t now = time(0);
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &now);
    timeStr[24] = '\0'; // 移除换行符

    // 转换日志级别为字符串
    std::string levelStr;
    switch (level)
    {
    case Level::Info:    levelStr = "信息"; break;
    case Level::Warning: levelStr = "警告"; break;
    case Level::Error:   levelStr = "错误"; break;
    }

    // 写入日志
    std::string logMessage = std::string(timeStr) + " [" + levelStr + "] " + message + "\n";
    logFile << logMessage;
    logFile.flush();

    // 同时输出到控制台
    std::cout << logMessage;
}

void Logger::Info(const std::string& message)
{
    Log(Level::Info, message);
}

void Logger::Warning(const std::string& message)
{
    Log(Level::Warning, message);
}

void Logger::Error(const std::string& message)
{
    Log(Level::Error, message);
}
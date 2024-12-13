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
        Info("��־ϵͳ��ʼ���ɹ�");
    }
}

void Logger::Log(Level level, const std::string& message)
{
    if (!isInitialized)
    {
        Init();
    }

    // ��ȡ��ǰʱ��
    time_t now = time(0);
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &now);
    timeStr[24] = '\0'; // �Ƴ����з�

    // ת����־����Ϊ�ַ���
    std::string levelStr;
    switch (level)
    {
    case Level::Info:    levelStr = "��Ϣ"; break;
    case Level::Warning: levelStr = "����"; break;
    case Level::Error:   levelStr = "����"; break;
    }

    // д����־
    std::string logMessage = std::string(timeStr) + " [" + levelStr + "] " + message + "\n";
    logFile << logMessage;
    logFile.flush();

    // ͬʱ���������̨
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
#pragma once
#include <string>
#include <fstream>

class Logger
{
public:
    // 日志级别
    enum class Level
    {
        Info,
        Warning,
        Error
    };

    static void Init(const std::string& filename = "GameEngine.log");
    static void Log(Level level, const std::string& message);
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);

private:
    static std::ofstream logFile;
    static bool isInitialized;
};
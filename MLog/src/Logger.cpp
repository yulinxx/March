#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>

#ifdef _WIN32
#include <stdlib.h> // _dupenv_s
#endif

namespace MLog
{
    // 获取用户主目录
//     std::string GetUserHomeDir()
//     {
// #ifdef _WIN32
//         char* buffer = nullptr;
//         size_t size = 0;

//         errno_t err = _dupenv_s(&buffer, &size, "USERPROFILE");
//         if (err == 0 && buffer != nullptr)
//         {
//             std::string homeDir(buffer);
//             free(buffer);
//             return homeDir;
//         }

//         err = _dupenv_s(&buffer, &size, "HOME");
//         if (err == 0 && buffer != nullptr)
//         {
//             std::string homeDir(buffer);
//             free(buffer);
//             return homeDir;
//         }

//         if (buffer)
//             free(buffer);
// #else
//         const char* homeDir = std::getenv("HOME");
//         if (!homeDir)
//         {
//             homeDir = std::getenv("USERPROFILE");
//         }
//         if (!homeDir)
//         {
//             return "."; // 如果环境变量不存在，返回当前目录
//         }
//         return std::string(homeDir);
// #endif
//     }

    // 清理超过指定天数的旧日志文件
    void CleanOldLogs(const std::filesystem::path& logDir, int maxDays)
    {
        auto now = std::chrono::system_clock::now();
        for (const auto& entry : std::filesystem::directory_iterator(logDir))
        {
            if (entry.is_regular_file())
            {
                auto lastWriteTime = std::filesystem::last_write_time(entry);
                auto fileTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
                auto duration = now - fileTime;
                auto age = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
                if (age > maxDays)
                {
                    std::filesystem::remove(entry.path());
                    std::cout << "Removed old log file: " << entry.path() << std::endl;
                }
            }
        }
    }

    class Logger::Impl
    {
    public:
        std::shared_ptr<spdlog::logger> logger;

        Impl()
        {
            //std::filesystem::path userHome = GetUserHomeDir();
            std::filesystem::path userHome = ".";
            std::filesystem::path logDir = userHome / "logs";
            std::filesystem::create_directories(logDir);

            CleanOldLogs(logDir, 7);

            std::string logPath = (logDir / "MarchApp.log").string();
            std::cout << "Log file path: " << logPath << std::endl;

            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("[%Y-%m-%d %T.%e] [%^%l%$] %v");
            console_sink->set_level(spdlog::level::info);

            auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(logPath, 0, 0);
            file_sink->set_pattern("[%Y-%m-%d %T.%e] [%l] %v");
            file_sink->set_level(spdlog::level::info);

            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
            logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());
            logger->set_level(spdlog::level::info); // 确保日志级别设置正确
            spdlog::register_logger(logger);
            spdlog::flush_every(std::chrono::seconds(10));

            // 测试日志输出
            // logger->info("This is a test log message.");
        }

        void log_info(const std::string& msg)
        {
            logger->info(msg);
        }
        void log_error(const std::string& msg)
        {
            logger->error(msg);
        }
    };

    std::unique_ptr<Logger::Impl> Logger::s_Impl;

    void Logger::Init()
    {
        s_Impl = std::make_unique<Impl>();
    }

    void Logger::LogInfo(const std::string& msg)
    {
        if (s_Impl)
            s_Impl->log_info(msg);
    }

    void Logger::LogError(const std::string& msg)
    {
        if (s_Impl)
            s_Impl->log_error(msg);
    }
} // namespace MLog
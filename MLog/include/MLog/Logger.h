#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <string>

#ifdef _WIN32
    #ifdef MLOG_EXPORTS
        #define MLOG_API __declspec(dllexport)
    #else
        #define MLOG_API __declspec(dllimport)
    #endif
#else
    #define MLOG_API
#endif


namespace MLog
{
    class Logger
    {
    public:
        MLOG_API static void Init();                            // 初始化日志
        MLOG_API static void LogInfo(const std::string& msg);   // 示例日志接口
        MLOG_API static void LogError(const std::string& msg);

    private:
        class Impl;  // 前向声明实现类
        static std::unique_ptr<Impl> s_Impl;  // 使用 unique_ptr 管理实现
    };
}

#endif  // LOGGER_H
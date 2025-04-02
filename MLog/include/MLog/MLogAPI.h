#ifndef MLOG_API_H
#define MLOG_API_H

// 定义 MLOG_API 宏
#ifdef MLOG_EXPORTS
#define MLOG_API __declspec(dllexport)
#else
#define MLOG_API __declspec(dllimport)
#endif
#else
#define MLOG_API
#endif

#endif // MLOG_API_H
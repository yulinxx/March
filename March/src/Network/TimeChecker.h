#ifndef TIME_CHECKER_H
#define TIME_CHECKER_H

#include <string>
#include <ctime>

class TimeChecker
{
public:
    TimeChecker() = default;

public:
    // 输入年月日，返回是否在指定时间前
    bool IsTimeValid(int year, int month = 1, int day = 1);

private:
    std::time_t GetNetworkTime(const std::string& url);
    bool IsBeforeDate(const std::string& url, int year, int month, int day);

};

#endif // TIME_CHECKER_H
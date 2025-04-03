#include "TimeChecker.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <curl/curl.h>

size_t WriteCallback(void* c, size_t sz, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)c, sz * nmemb);
    return sz * nmemb;
}

std::time_t TimeChecker::GetNetworkTime(const std::string& url)
{
    /*
    CURL* curl;
    CURLcode res;
    std::string headerData;
    curl = curl_easy_init();
    if (!curl)
        return -1;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // 只请求头部信息
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerData);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);

    // 解析 Date 头部
    std::string::size_type pos = headerData.find("Date:");
    if (pos != std::string::npos)
    {
        std::string dateStr = headerData.substr(pos + 6, 29); // RFC 7231 格式
        struct tm timeStruct = {};

#ifdef _WIN32
        std::istringstream ss(dateStr);
        ss >> std::get_time(&timeStruct, "%a, %d %b %Y %H:%M:%S GMT");
        if (ss.fail())
            return -1;
#else
        strptime(dateStr.c_str(), "%a, %d %b %Y %H:%M:%S GMT", &timeStruct);
#endif

        return mktime(&timeStruct);
    }
    */
    return -1;
}

bool TimeChecker::IsBeforeDate(const std::string& url, int year, int month, int day)
{
    std::time_t serverTime = GetNetworkTime(url);
    if (serverTime == -1)
        return false;

    struct tm targetDate = {};
    targetDate.tm_year = year - 1900;
    targetDate.tm_mon = month - 1;
    targetDate.tm_mday = day;
    targetDate.tm_hour = 0;
    targetDate.tm_min = 0;
    targetDate.tm_sec = 0;

    std::time_t targetTime = mktime(&targetDate);
    return serverTime < targetTime;
}

// 检查当前时间是否在传入的截止日期之后
bool TimeChecker::IsTimeValid(int year, int month /*=1*/, int day /*=1*/)
{
    std::string urlA = "https://www.baidu.com";
    bool bA = IsBeforeDate(urlA, year, month, day);
    if (bA)
        return true;

    std::string urlB = "https://www.google.com";
    bool bB = IsBeforeDate(urlB, year, month, day);
    if (bB)
        return true;

    return false;
}
#ifndef MENGINE_API_H
#define MENGINE_API_H

#ifdef _WIN32
    #ifdef MENGINE_EXPORTS
        #define MENGINE_API __declspec(dllexport)
    #else
        #define MENGINE_API __declspec(dllimport)
    #endif
#else
    #define MENGINE_API
#endif

#endif // MENGINE_API_H
#ifndef FILEHANDLER_API_H
#define FILEHANDLER_API_H

#ifdef _WIN32
#ifdef FILEHANDLER_EXPORTS
#define FILEHANDLER_API __declspec(dllexport)
#else
#define FILEHANDLER_API __declspec(dllimport)
#endif
#else
#define FILEHANDLER_API
#endif

#endif // FILEHANDLER_API_H
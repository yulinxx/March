#ifndef HARDWARE_API_H
#define HARDWARE_API_H

#ifdef _WIN32
#ifdef HARDWARE_EXPORTS
#define HARDWARE_API __declspec(dllexport)
#else
#define HARDWARE_API __declspec(dllimport)
#endif
#else
#define HARDWARE_API
#endif

#endif // HARDWARE_API_H
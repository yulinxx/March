#ifndef MRENDER_H
#define MRENDER_H

#ifdef _WIN32
#ifdef MRENDER_EXPORTS
#define MRENDER_API __declspec(dllexport)
#else
#define MRENDER_API __declspec(dllimport)
#endif
#else
#define MRENDER_API
#endif

#endif // MRENDER_H
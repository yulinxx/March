#ifndef PRE_INIT_H
#define PRE_INIT_H

#define __STDC_FORMAT_MACROS

#if defined(_WIN32)
#include <client/windows/handler/exception_handler.h>
#elif defined(__APPLE__)
#include <client/mac/handler/exception_handler.h>
#else
#include <client/linux/handler/exception_handler.h>
#endif

#if defined(_WIN32)
#else
static bool dumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                         void *context, bool succeeded)
{
    printf("Dump path: %s\n", descriptor.path());
    return succeeded;
}
#endif

using google_breakpad::ExceptionHandler;

// namespace BreakpadInit
// {
inline void PreInitialize()
{
#if defined(_WIN32)
    static google_breakpad::ExceptionHandler eh(
        L"crash_dumps",
        nullptr,
        nullptr,
        nullptr,
        google_breakpad::ExceptionHandler::HANDLER_ALL);
#else
    google_breakpad::MinidumpDescriptor descriptor("/tmp");
    google_breakpad::ExceptionHandler eh(descriptor, nullptr, dumpCallback, nullptr, true, -1);
#endif
}

// } // namespace BreakpadInit

#endif // PRE_INIT_H
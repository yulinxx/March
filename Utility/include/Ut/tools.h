#ifndef TOOLS_H
#define TOOLS_H

#include <type_traits>
#include <utility>

namespace Ut
{
    constexpr double PI = 3.14159265358979323846;
    constexpr double PIx2 = 2.0 * PI;
    constexpr double PIHalf = 0.5 * PI;
    constexpr double UT_EPSILON = 1e-6;
}

// 通用容器清理宏（线程不安全）
#define CLEAR_CONTAINER(container) \
do { \
    if (!container.empty()) { \
        using T = decltype(container); \
        if constexpr (requires { container.capacity(); }) { \
            T().swap(container); \
        } else { \
            container.clear(); \
        } \
    } \
} while(0)

// 类型安全的指针删除宏
// 编译时阻止 const 指针删除
#define SAFE_DEL(ptr) \
do { \
    if (ptr) { \
        static_assert(!std::is_const_v<std::remove_pointer_t<decltype(ptr)>>, \
                     "Cannot delete const-qualified pointer"); \
        if constexpr (std::is_array_v<std::remove_pointer_t<decltype(ptr)>>) { \
            delete[] ptr; \
        } else { \
            delete ptr; \
        } \
        ptr = nullptr; \
    } \
} while(0)

// 精确平台检测
#if defined(_WIN64)
#define PLATFORM_WINDOWS 64
#elif defined(_WIN32)
#define PLATFORM_WINDOWS 32
#elif defined(__APPLE__)
#define PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define PLATFORM_MACOS 1
#endif
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#endif

#endif // TOOLS_H
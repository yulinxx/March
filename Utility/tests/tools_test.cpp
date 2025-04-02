#include "Ut/tools.h"
#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <string>

// 测试 CLEAR_CONTAINER 宏
TEST(ToolsTest, ClearContainer)
{
    // 测试大vector
    {
        std::vector<int> v(1000, 42);
        size_t old_cap = v.capacity();
        CLEAR_CONTAINER(v);
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(0, v.capacity());
    }

    // 测试小string
    {
        std::string s(1000, 'a');
        size_t old_cap = s.capacity();
        CLEAR_CONTAINER(s);
        EXPECT_TRUE(s.empty());
        EXPECT_LT(s.capacity(), old_cap); // 只需确认容量减小
    }

    // 测试关联容器
    // {
    //     std::map<int, std::string> m;
    //     for (int i = 0; i < 1000; ++i) m[i] = "value";
    //     CLEAR_CONTAINER(m);
    //     EXPECT_TRUE(m.empty());
    // }

    // 测试空容器
    {
        std::vector<int> v;
        CLEAR_CONTAINER(v); // 不应崩溃
        EXPECT_TRUE(v.empty());
    }
}

// 测试 SAFE_DEL 宏
TEST(ToolsTest, SafeDelete)
{
    // 测试普通指针删除
    int* pInt = new int(42);
    EXPECT_NE(nullptr, pInt);
    SAFE_DEL(pInt);
    EXPECT_EQ(nullptr, pInt);

    // 测试数组指针删除
    int* pArray = new int[1000];
    EXPECT_NE(nullptr, pArray);
    SAFE_DEL(pArray);
    EXPECT_EQ(nullptr, pArray);

    // 测试空指针安全
    int* pNull = nullptr;
    SAFE_DEL(pNull);  // 不应崩溃
    EXPECT_EQ(nullptr, pNull);
}

// 测试平台检测宏
TEST(ToolsTest, PlatformDetection)
{
#if defined(PLATFORM_WINDOWS)
    std::cout << "Running on Windows platform" << std::endl;
#elif defined(PLATFORM_MACOS)
    std::cout << "Running on macOS platform" << std::endl;
#elif defined(PLATFORM_LINUX)
    std::cout << "Running on Linux platform" << std::endl;
#else
    FAIL() << "Unknown platform";
#endif
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
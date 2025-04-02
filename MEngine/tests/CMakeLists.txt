# 删除原有的 TEST_TARGETS 定义和各个 _SOURCES 定义

# 自动收集所有测试源文件
file(GLOB_RECURSE ALL_TEST_SOURCES 
    "*.cpp"
    "Command/*.cpp"
    "DrawData/*.cpp" 
    "Entity/*.cpp"
    "Scene/*.cpp"
)

# 创建单个测试可执行文件
add_executable(AllTests ${ALL_TEST_SOURCES})

# 配置包含目录和链接库
target_include_directories(AllTests PRIVATE 
    ${CMAKE_SOURCE_DIR}/MEngine/include/Eng
)

target_link_libraries(AllTests
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
    PRIVATE MEngine
    PRIVATE Utility
)

# 发现测试用例
include(GoogleTest)
gtest_discover_tests(AllTests)
# 自动收集所有测试源文件
file(GLOB_RECURSE ALL_TEST_SOURCES 
    "*.cpp"
    "Command/*.cpp"
    "DrawData/*.cpp" 
    "Entity/*.cpp"
    "Scene/*.cpp"
)

# 创建单个测试可执行文件
set(APP_NAME MEngineTests)
add_executable(${APP_NAME} ${ALL_TEST_SOURCES})

# 配置包含目录和链接库
target_include_directories(${APP_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/MEngine/include/
    ${CMAKE_SOURCE_DIR}/MEngine/include/Eng
)

target_link_libraries(${APP_NAME}
    PRIVATE GTest::gtest
    PRIVATE GTest::gtest_main
    PRIVATE MEngine
    PRIVATE Utility
)

# 发现测试用例
include(GoogleTest)
gtest_discover_tests(${APP_NAME})
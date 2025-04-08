# tests/CMakeLists.txt

# 定义 Vec 测试源文件列表
set(VEC_TEST_SOURCES
    VecTest.cpp
    VecTest2.cpp # 假设还有 VecTest2.cpp 文件
)

# 定义 Entity 测试源文件列表
# set(ENTITY_TEST_SOURCES
#     # XCEntity/XCEntityTest.cpp
#     XCEntity/XCArcTest.cpp
#     XCEntity/XCCircleTest.cpp
#     XCEntity/XCLineTest.cpp
#     XCEntity/XCPointTest.cpp
#     XCEntity/XCPolyBsplineTest.cpp
#     XCEntity/XCPolyLineTest.cpp
#     XCEntity/XCTextTest.cpp
# )

# 定义其他测试源文件列表，可根据实际情况添加
set(OTHER_TEST_SOURCES
    MatrixTest.cpp
    MatrixTestEx.cpp
    RectTest.cpp
    tools_test.cpp
    test_main.cpp
)

# 合并所有测试源文件
set(ALL_TEST_SOURCES ${VEC_TEST_SOURCES} ${ENTITY_TEST_SOURCES} ${OTHER_TEST_SOURCES})

# 定义一个函数来创建测试可执行文件并设置相关属性
function(create_test_executable test_name test_sources)
    add_executable(${test_name} ${test_sources})
    target_link_libraries(${test_name}
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
        PRIVATE Utility 
    )
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/Utility/include
    )
    gtest_discover_tests(${test_name})
endfunction()

# 创建单一的测试可执行文件
create_test_executable(UtilityTests "${ALL_TEST_SOURCES}")
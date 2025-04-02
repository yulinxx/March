cmake_minimum_required(VERSION 3.10)

# set(CMAKE_TOOLCHAIN_FILE D:/Install/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(MLog)


# 源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")


# 创建共享库
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
find_package(spdlog CONFIG REQUIRED)

# 定义导出宏
target_compile_definitions(${PROJECT_NAME} PRIVATE MLOG_EXPORTS)

# 链接并包含 spdlog（自动包含头文件路径）
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
#target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/MLog)

# 安装规则
# install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)
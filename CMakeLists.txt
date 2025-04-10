cmake_minimum_required(VERSION 3.10)

include(config.cmake)
include(tools.cmake)

# 设置VCPKG路径
# set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

# 设置项目名称
project(March VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Build mode judgment
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG_)  # Debug mode
    message("Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(_RELEASE_) # Release mode
    message("Release")
else()
    message(WARNING "CMAKE_BUILD_TYPE is not define")
endif()

# 去除警告
if(MSVC)
    add_compile_options("/wd4244")
    add_compile_options("/wd4251")
    add_compile_options("/wd4267")
    add_compile_options("/wd4819")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SILENCE_CXX23_DENORM_DEPRECATION_WARNING")
endif()

if(ENABLE_TEST)
    message("===== Enable testing =====")
endif()

# 统一配置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# add_subdirectory(FileHandler)
# add_subdirectory(HardwareControl)
add_subdirectory(MEngine)
add_subdirectory(MLog)
# add_subdirectory(MRenderInterface)
add_subdirectory(MRender)
add_subdirectory(Utility)
add_subdirectory(March)

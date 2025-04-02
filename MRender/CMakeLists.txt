cmake_minimum_required(VERSION 3.10)

project(MRender VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Qt的安装路径
set(Qt5_DIR ${Qt_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.h")
GroupHeaderFiles("${HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
FindAndGroupFiles(${CMAKE_CURRENT_SOURCE_DIR})

# 添加GLSL文件作为资源
configure_file(res/shader/vertex_shader.glsl vertex_shader.glsl COPYONLY)
configure_file(res/shader/fragment_shader.glsl fragment_shader.glsl COPYONLY)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE MRENDER_EXPORTS)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Render
    ${CMAKE_SOURCE_DIR}/MLog/include/
    ${CMAKE_SOURCE_DIR}/Utility/include/
    # ${CMAKE_SOURCE_DIR}/MRenderInterface/include/
    ${EIGEN3_INCLUDE_DIR}
    ${spdlog_INCLUDE_DIRS}
)

if(OUT_CMAKE_MSG)
message("===== ${PROJECT_NAME} 包含目录路径如下:")
message(STATUS "1. ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "2. ${CMAKE_SOURCE_DIR}/MLog/include")
message(STATUS "3. ${CMAKE_SOURCE_DIR}/Utility/include")
message(STATUS "4. ${EIGEN3_INCLUDE_DIR}")
message(STATUS "5. ${spdlog_INCLUDE_DIRS}")
message(" ==============\n")
endif(OUT_CMAKE_MSG)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    MLog
    Utility
    # MRenderInterface
    Qt5::Core
    Qt5::Widgets
    Qt5::OpenGL
    Eigen3::Eigen
)

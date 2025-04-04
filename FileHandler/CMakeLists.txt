cmake_minimum_required(VERSION 3.10)

project(FileHandler VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS "include/*.h")
GroupHeaderFiles("${HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
FindAndGroupFiles(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Eigen3 CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE FILEHANDLER_EXPORTS)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FH
    ${CMAKE_SOURCE_DIR}/MLog/include
    ${CMAKE_SOURCE_DIR}/MEngine/include
    ${CMAKE_SOURCE_DIR}/Utility/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen
    MLog
    MEngine
    Utility
)
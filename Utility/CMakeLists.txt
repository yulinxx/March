cmake_minimum_required(VERSION 3.10)

project(Utility VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 CONFIG REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.h")
GroupHeaderFiles("${HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
FindAndGroupFiles(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE UTILITY_EXPORTS)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Ut
    ${EIGEN3_INCLUDE_DIR}
)
# target_link_libraries(${PROJECT_NAME} PRIVATE 
#     Eigen3::Eigen
# )


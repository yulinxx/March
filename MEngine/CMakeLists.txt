cmake_minimum_required(VERSION 3.10)

project(MEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS "include/*.h")
GroupHeaderFiles("${HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
FindAndGroupFiles(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Eigen3 CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MENGINE_EXPORTS)
    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS OFF)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Eng
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/Eng/Command
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/Eng/DrawData
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/Eng/Scene
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/Eng/Entity
    ${CMAKE_SOURCE_DIR}/MLog/include
    ${CMAKE_SOURCE_DIR}/Utility/include
    ${CMAKE_SOURCE_DIR}/FileHandler/include
    # ${CMAKE_SOURCE_DIR}/MRenderInterface/include
)

# 链接 Boost 库
if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen
    MLog
    Utility
)



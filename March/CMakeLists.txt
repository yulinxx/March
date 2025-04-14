cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(March VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动处理 Qt 的 moc、uic 和 rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置Qt的安装路径
set(Qt5_DIR ${Qt_DIR})

# 查找Qt库
find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.h")
GroupHeaderFiles("${HEADERS}" "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
FindAndGroupFiles(${CMAKE_CURRENT_SOURCE_DIR})

# set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/EntityFactory.cpp)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/MEngine/include/
    ${CMAKE_SOURCE_DIR}/MRender/include/
    ${CMAKE_SOURCE_DIR}/MLog/include/
)

if(OUT_CMAKE_MSG)
message("${PROJECT_NAME} 包含目录路径如下:")
message(STATUS "1. ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "2. ${CMAKE_SOURCE_DIR}/MEngine/include")
message(STATUS "3. ${CMAKE_SOURCE_DIR}/MRender/include")
message(STATUS "4. ${CMAKE_SOURCE_DIR}/MLog/include")
message(" ==============\n")
endif(OUT_CMAKE_MSG)

find_package(Eigen3 CONFIG REQUIRED)

# 链接Log库到主工程和其他子工程
target_link_libraries(${PROJECT_NAME} PRIVATE MRender MLog MEngine Utility)


# 链接第三方库
# 链接Qt库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${Qt5_DIR}/../../../bin/macdeployqt $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Deploying Qt libraries for macOS"
    )
endif()

# set(EXECUTE_WINDOWS_SETUP OFF CACHE BOOL "Enable Windows specific setup")
set(EXECUTE_WINDOWS_SETUP ON CACHE BOOL "Enable Windows specific setup")
if(WIN32 AND EXECUTE_WINDOWS_SETUP)
    # Windows 特定设置
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "MarchCAD"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${Qt_INSTALL_DIR}/bin/windeployqt.exe" "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Deploying Qt libraries for Windows"
    )
endif()

# Qt资源编译
qt_add_resources(RESOURCES
  res/resources.qrc
)

# 将资源文件链接到可执行文件
target_sources(${PROJECT_NAME} PRIVATE
  ${RESOURCES}
)

# 安装目标
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)


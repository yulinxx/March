
##################################################################
# set(VCPKG_DIR "D:/Install/vcpkg/")
set(VCPKG_DIR "/home/x/Install/vcpkg/")
#set(VCPKG_DIR "C:/vcpkg/")

if(WIN32)
    #set(VCPKG_DIR "C:/vcpkg/")
    set(VCPKG_DIR "D:/Install/vcpkg/")
elseif(UNIX AND NOT APPLE)
    set(VCPKG_DIR "/home/x/Install/vcpkg/")
elseif(APPLE)
    set(VCPKG_DIR "/path/to/mac/vcpkg/")
endif()


if(WIN32)
    set(Qt_INSTALL_DIR "C:/Qt/5.15.2/msvc2019_64/")
    set(Qt_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
elseif(UNIX AND NOT APPLE)
    set(Qt_INSTALL_DIR "/home/x/Install/Qt/5.15.2/gcc_64/")
    set(Qt_DIR "/home/x/Install/Qt/5.15.2/gcc_64/lib/cmake/Qt5/")
elseif(APPLE)
    set(Qt_INSTALL_DIR "/path/to/mac/Qt/5.15.2/clang_64/")
    set(Qt_DIR "/path/to/mac/Qt/5.15.2/clang_64/lib/cmake/Qt5/")
endif()


#set(OUT_CMAKE_MSG  TRUE)
set(OUT_CMAKE_MSG TRUE)

option(ENABLE_GTEST "Enable Google Test" ON)
#option(ENABLE_GTEST "Enable Google Test" ON)

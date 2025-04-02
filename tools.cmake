
##################################################################
# 获取所有子目录,返回其绝对路径
# 查找指定文件夹下的所有子目录的头文件和源文件(仅目录名)
# 要查找的目录  得到的所有子目录绝对路径  要排除的文件夹名称
function(GetSubDir FindDir ResDir ExcludeDirs)
    file(GLOB SubDirs RELATIVE ${FindDir} ${FindDir}/*)
    set(FindDirList "")

    set(SkipDir TRUE)
    if(NOT DEFINED ExcludeDirs)
        set(SkipDir FALSE)
    endif()

    foreach(CurDir ${SubDirs})

        if(IS_DIRECTORY ${FindDir}/${CurDir})
            set(AddFlag TRUE)

            if(SkipDir)
                foreach(exc ${ExcludeDirs})
                    if("${CurDir}" STREQUAL "${exc}")
                        set(AddFlag FALSE)
                        break()
                    endif()
                endforeach()
            endif()

            if(AddFlag)
                list(APPEND FindDirList ${FindDir}/${CurDir})

                # 递归调用
                set(subDirs "")
                GetSubDir(${FindDir}/${CurDir} subDirs "${ExcludeDirs}")

                # 收集递归调用返回的目录
                list(APPEND FindDirList ${subDirs})
            endif()
        endif()
    endforeach()

    set(${ResDir} ${FindDirList} PARENT_SCOPE)
endfunction()


##################################################################

# 查找当前文件夹下的所有子目录
# 要查找的目录  得到的所有子目录  要排除的文件夹名称
function(GetSubDir2 FindDir ResDir  ExcludeDirs)
    file(GLOB SubDirs RELATIVE ${FindDir} ${FindDir}/*)
    set(FindDirList "")

    foreach(CurDir ${SubDirs})
        if(IS_DIRECTORY ${FindDir}/${CurDir})
            SET(AddFlag TRUE)

            foreach(exc ${ExcludeDirs})
                if("${CurDir}" STREQUAL "${exc}" )
                    SET(AddFlag FALSE)
                    BREAK()
                endif()
            endforeach()

            if(${AddFlag})
                list(APPEND FindDirList ${CurDir})

                # 递归调用
                GetSubDir2(${FindDir}/${CurDir} subDirs "${ExcludeDirs}")
                list(APPEND FindDirList ${subDirs})
            endif()

        endif()

    endforeach()
    set(${ResDir} ${FindDirList} PARENT_SCOPE)
endfunction()

##################################################################
# 获取路径列表中，所有的头文件和源文件
function(GetFiles DIR_LIST HEADER_FILES SRC_FILES)
    set(Header_List "")
    set(Src_List "")

    #message("\n\n\n********  ${DIR_LIST}")

    foreach(dir ${DIR_LIST})
        # 递归查找
        # file(GLOB_RECURSE curr_headers ${dir}/*.h)
        # file(GLOB_RECURSE curr_sources ${dir}/*.cpp ${dir}/*.c)

        file(GLOB curr_headers ${dir}/*.h ${dir}/*.hpp ${dir}/*.inl)
        file(GLOB curr_sources ${dir}/*.cpp ${dir}/*.c ${dir}/*.cc  ${dir}/*.cxx)

        list(APPEND Header_List ${curr_headers})
        list(APPEND Src_List ${curr_sources})
    endforeach()

    set(${HEADER_FILES} ${Header_List} PARENT_SCOPE)
    set(${SRC_FILES} ${Src_List} PARENT_SCOPE)
endfunction()


##################################################################

# 将头文件分组 头文件列表 要删除的路径
# 将头文件的完整路径删除掉指定的路径部分，使用剩余的路径进行分组
function(GroupHeaderFiles HEADER_FILES DelPath)
    foreach(headerFile ${HEADER_FILES})
        get_filename_component(headerDir ${headerFile} PATH)
        string(REPLACE ${DelPath} "" groupHeaderDir ${headerDir})

        if(NOT groupHeaderDir STREQUAL "")
            string(REPLACE "/" "\\" groupHeaderDir ${groupHeaderDir})
        else()
            set(groupHeaderDir "\\")
        endif()

        source_group("Header Files\\${groupHeaderDir}" FILES ${headerFile})
    endforeach()

endfunction()


##################################################################
# 将源文件分组
function(GroupSrcFiles SRC_FILES DelPath)
    foreach(srcFile ${SRC_FILES})
        get_filename_component(srcDir ${srcFile} PATH)
        string(REPLACE ${DelPath} "" groupSrcDir  ${srcDir})
        
        if(NOT groupSrcDir  STREQUAL "")
            string(REPLACE "/" "\\" groupSrcDir  ${groupSrcDir})
        else()
            set(groupSrcDir "\\")
        endif()

        source_group("Source Files\\${groupSrcDir}" FILES ${srcFile})

    endforeach()

endfunction()

##################################################################



##################################################################
# 拷贝文件排除指定格式
function(CopyFile target srcDir dstDir extFileLst extDocLst)
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory "${dstDir}"
      VERBATIM
      )
    file(GLOB all_files RELATIVE ${srcDir} ${srcDir}/*)
    foreach(file ${all_files})   
        # 判断是否为文件夹
        if(IS_DIRECTORY ${srcDir}/${file})
            get_filename_component(DocName ${srcDir}/${file} NAME)
            list(FIND extDocLst "${DocName}" is_excluded)
            if(is_excluded EQUAL -1)
                add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${dstDir}/${file}"
                VERBATIM
                )
            COPY_COMMAND(${target} ${srcDir}/${file} ${dstDir}/${file})
            endif()
        else()
            # 获取文件扩展名
            get_filename_component(extension ${srcDir}/${file} EXT)
            # 检查文件扩展名是否在排除列表中
            list(FIND extFileLst "${extension}" is_excluded)
 
            if (is_excluded EQUAL -1)
            COPY_COMMAND(${target} ${srcDir}/${file} ${dstDir})			
            endif()
        endif()
    endforeach()

endfunction()

##################################################################

macro(COPY_COMMAND target source_file target_dir)
  string(FIND ${source_file} "$<CONFIGURATION>" _pos)
  if(NOT ${_pos} EQUAL -1)
    # Must test with an actual configuration directory.
    string(REPLACE "$<CONFIGURATION>" "Release" existing_source_file ${source_file})
    if(NOT EXISTS ${existing_source_file})
      string(REPLACE "$<CONFIGURATION>" "Debug" existing_source_file ${source_file})
    endif()
  else()
    set(existing_source_file ${source_file})
  endif()

  if(IS_DIRECTORY ${existing_source_file})
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_file}" "${target_dir}"
      VERBATIM
      )
  else()
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source_file}" "${target_dir}"
      VERBATIM
      )
  endif()
endmacro()

##################################################################

function(FindAndGroupFiles PROJECT_DIR)
    file(GLOB_RECURSE HEADERS "${PROJECT_DIR}/include/*.h")
    GroupHeaderFiles("${HEADERS}" "${PROJECT_DIR}")

    if(OUT_CMAKE_MSG)
        message(" ===== 头文件路径如下:")
        foreach(HEADER_FILE ${HEADERS})
            message(STATUS ${HEADER_FILE})
        endforeach(HEADER_FILE)
        message(" ==============\n")
    endif(OUT_CMAKE_MSG)

    file(GLOB_RECURSE SOURCES "${PROJECT_DIR}/src/*.cpp")
    GroupSrcFiles("${SOURCES}" "${PROJECT_DIR}")

    if(OUT_CMAKE_MSG)
        message(" ===== 源文件路径如下:")
        foreach(SOURCE_FILE ${SOURCES})
            message(STATUS ${SOURCE_FILE})
        endforeach(SOURCE_FILE)
        message(" ==============\n")
    endif(OUT_CMAKE_MSG)
endfunction()
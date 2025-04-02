@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

REM ========================
REM 作用: 合并 Git 拉取、推送与 CMake 生成操作
REM ========================

echo ========================
echo 欢迎使用 MantiSoft 自动化脚本
echo ========================

echo.
echo 请选择操作:
echo 1: 拉取 MantiSoft 及所有子仓库的 origin/upstream 并合并到本地
echo 2: 推送 MantiSoft 及所有子仓库的暂存区内容 到远端服务器 origin/upstream
echo 3: 构建 CMake,生成 VS2022 的工程文件 .sln,并启动 VS2022 打开
echo 4: 仅查看仓库状态
echo.

REM 设置主目录
set main_dir=D:\CAD\

REM 设置子仓库列表
set "submodules=Algorithm CadCore Depends FileParser OpenGLRHI PathOptimization PolygonFill RDCAM RdImgProcess RDNet RenderInterface RHI_DX11 RuiDaUi UiInterface WHBusCAM WuHanRuiDaUi"

set /p choice="请输入 1(拉)、2(推) 或 3(CMake) 4(Git仓库状态) (默认 1):  "
if "%choice%"=="" set choice=1

if "%choice%"=="1" goto git_pull_and_merge
if "%choice%"=="2" goto git_push_changes
if "%choice%"=="3" goto cmake_generate
if "%choice%"=="4" goto git_status
echo 输入错误，请重新运行脚本。
pause
exit

REM *******************************************************
REM 根据输入，决定是推拉还是查看
:git_pull_and_merge
set git_action=pull
goto git_process

:git_push_changes
set git_action=push
goto git_process

:git_status
set git_action=status
goto git_process


REM ***********************************************************
:git_process
echo.
echo =========================
if "!git_action!"=="push" (
    echo 开始推送 Git 仓库的内容
) 
if "!git_action!"=="pull" (
    echo 开始拉取并合并 Git 仓库的内容
) 
if "!git_action!"=="status" (
    echo 查看 Git 仓库的状态
)
echo =========================
echo.

REM 确定主仓库路径
set /p chooseRep="1 MantiSoft 2 Upstream 3 MantiSoftX:  "
if "%chooseRep%"=="" (
    set chooseRep=1
)
if "%chooseRep%"=="1" (
    set rep_path=MantiSoft
) 
if "%chooseRep%"=="2" (
    set rep_path=Upstream
) 
if "%chooseRep%"=="3" (
    set rep_path=MantiSoftX
) 
if not "%chooseRep%"=="1" if not "%chooseRep%"=="2" if not "%chooseRep%"=="3" (
    set rep_path=MantiSoft
)
set source_dir=%main_dir%%rep_path%

REM ========================
REM 验证主仓库路径
REM ========================
if not exist "%source_dir%" (
    echo 主目录不存在: %source_dir%
    pause
    exit
)

echo.
echo 主目录路径: %source_dir%

REM 处理主目录及子仓库
call :process_git_directory "%source_dir%"


REM 遍历子仓库并处理
for %%s in (%submodules%) do (
    echo.
    echo ===================================================================
    echo.
    echo ============== %%s ==============
    set "submodule_dir=%source_dir%\%%s"
    echo 子模块路径: !submodule_dir!

    if exist "!submodule_dir!\.git" (
        call :process_git_directory "!submodule_dir!"
    ) else (
        echo 子仓库目录不存在或未初始化: %%s
    )
)

echo.
echo ============== 操作完成 ==============
pause
exit

REM *******************************************************
:process_git_directory
REM 处理单个 Git 仓库的推送或拉取
echo.
echo 正在处理仓库: %~1
cd /d "%~1" || (
    echo 无法访问目录: %~1
    goto :eof
)

REM 检查是否为 Git 仓库
git rev-parse --is-inside-work-tree >nul 2>&1 || (
    echo 当前目录不是有效的 Git 仓库: %~1
    goto :eof
)

echo.
echo git remote -v
git remote -v
echo ----------------
echo.
git status
echo ----------------

REM 执行推送,拉取或查看逻辑
if "%git_action%"=="pull" (
    echo.
    echo 拉取远程分支upstream并合并到本地... git fetch upstream and merge to master
    git fetch upstream
    git merge upstream/master
    echo.
    echo 拉取远程分支origin... git fetch origin and merge to master
    git fetch origin
    git merge origin/master
    echo.
) else if "%git_action%"=="push" (
    echo.
    echo 推送到远程分支... git push origin/upstream master
    git push origin master
    echo.
    git push upstream master
    echo.
) else (
    echo.
    git log -1
    echo.
)
goto :eof


REM ***********************************************************
:cmake_generate
echo.
echo =========================
echo 开始生成 CMake 工程文件
echo =========================
echo.

REM 选择仓库
set /p chooseRep="指定仓库：1: MantiSoft, 2: Upstream 3 X(输入1,2,3 / 默认MantiSoft): "
if "%chooseRep%"=="" (
    set rep_path=MantiSoft
) 
if "%chooseRep%"=="1" (
    set rep_path=MantiSoft
) 
if "%chooseRep%"=="2" (
    set rep_path=Upstream
) 
if "%chooseRep%"=="3" (
    set rep_path=MantiSoftX
)

REM 设置源代码目录
set source_dir=%main_dir%%rep_path%

REM 选择生成版本位数
set /p chooseVer="生成版本位数：64/32 位, 1: 64, 2: 32 (输入1或2 / 默认64位): "
if "%chooseVer%"=="2" (
    set build_dir=%main_dir%%rep_path%_Build_X86
    set platform=Win32
) else (
    set build_dir=%main_dir%%rep_path%_Build_X64
    set platform=x64
)

REM 清理构建目录
set /p confirm="清理构建目录 '%build_dir%' ？(输入1 清理 或2 不清理 / 默认不清理): "

echo.
echo.
echo.

mkdir "%build_dir%"

if /i "%confirm%"=="1" (
    if exist "%build_dir%" (
        echo 正在清理构建目录...
        rmdir /s /q "%build_dir%"
    )
    mkdir "%build_dir%"
)



REM 切换到构建目录
cd /d "%build_dir%"

REM 运行 CMake 命令
echo 正在执行 CMake 命令...
cmake -G "Visual Studio 17 2022" -A %platform% "%source_dir%"
if %errorlevel% neq 0 (
    echo CMake 配置失败，请检查错误信息。
    pause
    exit /b
)

REM 打开解决方案文件
set solution_file=%build_dir%\MantiSoft.sln
if exist "%solution_file%" (
    echo.
    echo 正在打开解决方案文件：%solution_file%
    echo.
    start "" "%solution_file%"
) else (
    echo 解决方案文件不存在，请确保构建过程正确生成了解决方案文件。
)

pause
exit

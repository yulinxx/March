# March 框架文档

## 1. 使用方法
项目基于Qt5.15.2开发，使用CMake进行编译。可以使用Visual Studio 2022或Qt Creator进行编译。且支持Windows、Linux、Mac等平台。符合各种开源库的开发使用规范。

### 1.1 环境准备
- 确保已经安装了 CMake, VCPKG 和 Qt 开发环境
  - CMake 3.10 或更高版本
  - Qt 5.15.2 
  - VCPKG
  - IDE: VSCode 或者 VS2022 等 

-  VCPKG 所需的库：
  - spdlog 1.11.0
  - boost 1.81.0
  - eigen 3.4.0

- 其它需求:
  - C++ 23 或更高版本

### 1.2 编译
- 根据操作系统及安装路径,修改 config.h 中的 VCPKG_DIR,Qt_DIR 等参数，确保路径正确。
- 使用CMake工具或IDE进行编译


## 2. March框架简介
March框架是一个基于Qt和OpenGL的多文档图形编辑框架，提供了丰富的图形编辑功能，支持点、线、圆、矩形等基本图形元素的绘制、编辑、缩放、旋转等操作。

## 1. 核心架构概述
采用分层架构设计，主要分为：

- FileHandler 
  - 文件处理工程库：提供文件读写功能,为程序提供文件读写功能
- HardwareHandler 
  - 硬件处理工程库：提供硬件信息获取功能,为程序提供硬件信息获取功能
- March 
  - UI主工程EXE ：基于Qt的主窗口和控件
- MEngine 
  - 数据算法工程库 ：场景和图元管理,以及对数据的中转
- MLog 
  - 日志工程库：日志记录组件,为各工程库提供日志记录功能
- MRender 
  - 视图工程库 ：OpenGL渲染组件,使用数据
- MRenderInterface 
  - 渲染接口工程库：提供渲染接口,为各工程库提供渲染功能
- Utils
  - 工具工程库：工具类,为各工程库提供工具类

###  FileHandler 
预留

###  HardwareHandler
预留

###  March
- MainWindow 作为主窗口类：class MainWindow : public QMainWindow
    里面嵌套了一个  m_tabView ：m_tabView = new QTabWidget(this);
以及还有一些工具条： 绘图工具条  编辑工具条  显示工具条  帮助工具条  状态栏 等

- m_tabView 中添加了一个 viewWrapper：class ViewWrapper : public QWidget,
  且绘图操作的鼠标交互都在 viewWrapper 中处理.

- viewWrapper 又有两个成员变量：  m_glView（MarchView，用于渲染）和 m_scene（Scene，用于数据管理）。
m_glView = new MRender::MarchView(this);  
m_scene = new MEngine::Scene();  

- Operation 作为操作类：绘制点、线、圆、矩形等图形元素的操作类。
使用策略模式, 不同的操作类实现不同的操作, 并在 ViewWrapper 中进行交互绘制。

- OptAdapter 则作为操作适配器类：
使用适配器, 将不同的控件操作转发至此类中,并调用相应的操作,使得操作类与控件解耦。

### MEngine
 - Command 
   - 命令模式：用于实现撤销和重做功能, 支持对图形元素的添加、删除、修改等操作。

- DrawData
   - 数据绘制类：用于获取图形元素, 包括点、线、圆、矩形等, 以及辅助的预览元素.
  
- Entity 
   - 则为图元类,目前大致写了一些,实现基础的绘制与选择及移动等,后续根据实际数据结构进行修改扩展

- Scene
   - 场景类：用于管理所有图形元素, 以及图层,命令等
   - 图元的添加, 删除, 群组, 选择都在此中进行

### MLog
在SPDLOG基础上封装的日志组件,为各工程库提供日志记录功能

### MRender
- MarchView
  - 基于OpenGL 4.6的图形渲染
  - 接收MEngine的数据据并进行绘制

### MRenderInterface
预留

### Utils
给各工程库提供通用的工具函数,以及数据定义,方便DLL间蝗数据传递

### 1.1 主要组件
- Vec 
  - 向量类：封装了二维和三维向量的操作

- tools
 - 包含一些常用的宏定义和工具函数

- Matrix
  - 矩阵类：封装了二维和三维矩阵的操作

- XCEntity 
  - 为图元的定义声明,现未使用


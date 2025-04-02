#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

#include "Menu/MenuBar.h"
#include "TopInfoToolBar/InfoToolBar.h"
#include "LeftDrawToolBar/DrawToolBar.h"
#include "RightHardInfoDock/HardInfoDock.h"
#include "BottomStatusInfoBar/StatusInfoBar.h"
#include "BottomColorLayer/ColorLayerBar.h"
#include "Widgets/RenderView/ViewWrapper.h"
#include "OptAdapter/EntityDrawAdapter.h"
#include "OptAdapter/FileAdapter.h"
#include "OptAdapter/MsgAdapter.h"

/**
 * @class MainWindow
 * @brief 应用程序主窗口类，负责管理界面各核心组件
 *
 * 该类整合了菜单栏、工具栏、绘图工具条、硬件信息面板、状态栏
 * 和3D渲染视图等核心界面组件。
 */
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    // 获取主菜单栏对象
    MenuBar* getMenuBar() const;
    // 获取主工具栏对象
    InfoToolBar* getMainToolBar() const;
    // 获取绘图工具条对象
    DrawToolBar* getDrawToolBar() const;
    // 获取硬件信息面板对象
    HardInfoDock* getHardInfoDock() const;

    // 获取状态栏对象
    StatusInfoBar* getStatusBar() const;

    // 获取视图ab
    QTabWidget* getViewTab() const;

    // 获取渲染视图对象
    QList<ViewWrapper*> getAllViews() const;
    ViewWrapper* getView() const;

    // 新建视图
    void createNewView();

    void updateScene();
    
private:
    // 初始化界面布局和组件
    void initUI();

    // 初始化数据
    void initData();

private:
    EntityDrawAdapter* m_entityAdapter{ nullptr }; // 图元工厂适配器
    FileAdapter* m_fileAdapter{ nullptr }; // 文件适配器
    MsgAdapter* m_msgAdapter{ nullptr }; // 提示适配器

    MenuBar* m_menuBar{ nullptr };              // 主菜单栏组件
    InfoToolBar* m_mainToolBar{ nullptr };      // 顶部信息工具栏
    DrawToolBar* m_drawToolBar{ nullptr };      // 左侧绘图工具条
    HardInfoDock* m_hardInfoDock{ nullptr };    // 右侧硬件信息停靠面板
    ColorLayerBar* m_colorLayer{ nullptr };     // 颜色选择面板
    StatusInfoBar* m_statusBar{ nullptr };      // 底部状态信息栏

    ViewWrapper* m_view{ nullptr };             // 包装了渲染视图组件

    QTabWidget* m_tabView{ nullptr };

};

#endif // MAINWINDOW_H
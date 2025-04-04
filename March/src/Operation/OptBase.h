#ifndef OPTBASE_H
#define OPTBASE_H

#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include "def.h"

#include "Widgets/RenderView/ViewWrapper.h"
#include "Scene/Scene.h"


//class ViewWrapper;
namespace MRender { class MarchView; }
class IOperation;

class OptBase
{
public:
    OptBase(MEngine::Scene* scene);
    virtual ~OptBase();

public:
    virtual void enter();
    virtual void exit();

    // 定义鼠标和键盘事件的虚函数
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    virtual void wheelEvent(QWheelEvent* event);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void resizeEvent(QResizeEvent* event);

    virtual void enterEvent(QEnterEvent* event);
    virtual void leaveEvent(QEvent* event);


public:
    void resetView();

    void setViewWidget(ViewWrapper* parent);
    void setGLView(MRender::MarchView* glView);

    DrawType getDrawType() { return m_drawType; }

//private:
public:
    DrawType m_drawType = DrawType::Select;

    ViewWrapper* m_viewWrap = nullptr;
    MEngine::Scene* m_scene = nullptr;
    MRender::MarchView* m_glView = nullptr;

    QPoint m_lastPos;
    qint64 m_lastMiddleClickTime = 0; // 中键点击时间
    QPoint m_lastMiddlePos; // 鼠标位置
    bool m_bPanning = false; // 是否平移
    QPoint m_lastPanPos; // 上次平移位置

    // 窗、交选
    bool m_bSelecting = false;
    Ut::Vec2d m_selectStart;
    Ut::Vec2d m_selectEnd;

};

#endif // OPTBASE_H
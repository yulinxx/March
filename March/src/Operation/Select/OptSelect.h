#ifndef OPTSELECT_H
#define OPTSELECT_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Rectangle;

}

class OptSelect : public OptBase
{
    using Super = OptBase;

public:
    OptSelect(MEngine::Scene* scene);
    virtual ~OptSelect();

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
    //void resetView();

    //void setViewWidget(ViewWrapper* parent);
    //void setGLView(MRender::MarchView* glView);

    //DrawType getDrawType();


    //private:
public:
    DrawType m_drawType = DrawType::Select;

    // ViewWrapper* m_viewWrap = nullptr;
    // MEngine::Scene* m_scene = nullptr;
    // MRender::MarchView* m_glView = nullptr;

    // QPoint m_lastPos;
    // qint64 m_lastMiddleClickTime = 0; // 中键点击时间
    // QPoint m_lastMiddlePos; // 鼠标位置
    // bool m_bPanning = false; // 是否平移
    // QPoint m_lastPanPos; // 上次平移位置

    // 窗、交选
    bool m_bSelecting = false;
    bool m_bMoving = false;
    Ut::Vec2d m_posStart;
    Ut::Vec2d m_posEnd;

    std::shared_ptr<MEngine::Rectangle> m_rectPreview = nullptr;



};

#endif // OPTSELECT_H
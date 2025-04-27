#ifndef OPTSELECT_H
#define OPTSELECT_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Rectangle;

}

class OptSelect : public OptBase
{
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
    void showEntityInfo();
    void showEntityInfo(std::shared_ptr<MEngine::Entity> entity);
    //void resetView();

    //void setViewWidget(ViewWrapper* parent);
    //void setGLView(MRender::MarchView* glView);

    //DrawType getDrawType();


    //private:
public:
    DrawType m_drawType = DrawType::Select;

    // 窗、交选
    bool m_bSelecting = false;
    bool m_bMoving = false;
    Ut::Vec2d m_posStart;
    Ut::Vec2d m_posEnd;

    std::shared_ptr<MEngine::Rectangle> m_rectPreview = nullptr;



};

#endif // OPTSELECT_H
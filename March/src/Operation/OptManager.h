#ifndef OPTMANAGER_H
#define OPTMANAGER_H

#include "def.h"
#include "OptBase.h"
#include <memory>

class ViewWrapper;

namespace March
{
    class MarchView;
}

namespace MEngine
{
    class Scene;
}

class OptManager final
{
public:
    explicit OptManager(ViewWrapper* viewWidget,
        MEngine::Scene* scene,
        MRender::MarchView* glView
    );

public:
    void set(int nType);
    void setDefaultOpt();

    // 事件转发接口
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event);

    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);

private:
    std::shared_ptr<OptBase> m_selectOpt = nullptr;
    std::shared_ptr<OptBase> m_curOpt = nullptr;

    ViewWrapper* m_viewWrap = nullptr;
    MRender::MarchView* m_glView = nullptr;
    MEngine::Scene* m_scene = nullptr;

};

#endif // OPTMANAGER_H
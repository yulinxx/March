#include "OptDrawSpline.h"

OptDrawSpline::OptDrawSpline(MEngine::Scene* scene) : OptBase(scene) {}

OptDrawSpline::~OptDrawSpline() {}

// 实现enter()函数
void OptDrawSpline::enter()
{
    // 这里可以添加进入绘制样条曲线操作时的具体逻辑
    // 例如，初始化样条曲线绘制所需的数据、显示提示信息等
}

// 实现exit()函数
void OptDrawSpline::exit()
{
    // 这里可以添加退出绘制样条曲线操作时的具体逻辑
    // 例如，清理样条曲线绘制相关的数据、保存状态等
}

void OptDrawSpline::mousePressEvent(QMouseEvent* event)
{
}

void OptDrawSpline::mouseReleaseEvent(QMouseEvent* event)
{
}

void OptDrawSpline::mouseMoveEvent(QMouseEvent* event)
{
}
void OptDrawSpline::wheelEvent(QWheelEvent* event)
{
}

void OptDrawSpline::keyPressEvent(QKeyEvent* event)
{
}
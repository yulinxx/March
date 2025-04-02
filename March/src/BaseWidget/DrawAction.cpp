#include "DrawAction.h"

// 原有的 5 个参数的构造函数实现
DrawAction::DrawAction(const QIcon& normalIcon, const QIcon& hoverIcon, const QIcon& pressedIcon, const QString& text, QObject* parent)
    : QAction(normalIcon, text, parent), m_normalIcon(normalIcon), m_hoverIcon(hoverIcon), m_pressedIcon(pressedIcon)
{
    setHovered(false);
    setPressed(false);
}

// 新增的 3 个参数的构造函数实现，调用原有的 5 个参数的构造函数
DrawAction::DrawAction(const QIcon& normalIcon, const QString& text, QObject* parent)
    : DrawAction(normalIcon, normalIcon, normalIcon, text, parent)
{
    // 这里可以添加额外的初始化代码，如果需要的话
}

// 设置悬浮状态
void DrawAction::setHovered(bool hovered)
{
    if (hovered)
    {
        setIcon(m_hoverIcon);
    }
    else
    {
        setIcon(m_normalIcon);
    }
}

// 设置点击状态
void DrawAction::setPressed(bool pressed)
{
    if (pressed)
    {
        setIcon(m_pressedIcon);
    }
    else
    {
        setIcon(m_normalIcon);
    }
}
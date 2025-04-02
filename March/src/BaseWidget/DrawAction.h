#ifndef DRAWACTION_H
#define DRAWACTION_H

#include <QDockWidget>
#include <QAction>
#include <QIcon>
#include <QLayout>
#include "def.h"
#include "../Widgets/TipWidget.h"

// 自定义 DrawAction 类
class DrawAction : public QAction
{
    Q_OBJECT
public:
    // 原有的 5 个参数的构造函数
    DrawAction(const QIcon& normalIcon, const QIcon& hoverIcon, const QIcon& pressedIcon, const QString& text, QObject* parent = nullptr);
    // 新增的 3 个参数的构造函数，为缺失的参数提供默认值
    DrawAction(const QIcon& normalIcon, const QString& text, QObject* parent = nullptr);

    void setHovered(bool hovered);
    void setPressed(bool pressed);

private:
    QIcon m_normalIcon;
    QIcon m_hoverIcon;
    QIcon m_pressedIcon;
};

#endif // DRAWACTION_H
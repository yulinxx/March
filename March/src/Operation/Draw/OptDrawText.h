#ifndef OPTDRAWTEXT_H
#define OPTDRAWTEXT_H

#include "Operation/OptBase.h"


class OptDrawText : public OptBase
{
public:
    OptDrawText(MEngine::Scene* scene);
    ~OptDrawText() override;

    // 实现enter()和exit()函数
    void enter() override;
    void exit() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:

};

#endif // OPTDRAWTEXT_H
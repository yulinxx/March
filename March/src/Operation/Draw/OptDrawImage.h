#ifndef OPTDRAWIMAGE_H
#define OPTDRAWIMAGE_H

#include "Operation/OptBase.h"

class OptDrawImage : public OptBase
{
public:
    OptDrawImage(MEngine::Scene* scene);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    // 可添加相关成员变量
};

#endif // OPTDRAWIMAGE_H
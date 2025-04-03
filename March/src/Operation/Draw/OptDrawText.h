#ifndef OPTDRAWTEXT_H
#define OPTDRAWTEXT_H

#include "Operation/OptBase.h"


class OptDrawText : public OptBase
{
public:
    OptDrawText(MEngine::Scene* scene);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:

};

#endif // OPTDRAWTEXT_H
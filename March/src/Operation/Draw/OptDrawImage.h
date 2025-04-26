#ifndef OPTDRAWIMAGE_H
#define OPTDRAWIMAGE_H

#include "Operation/OptBase.h"

class OptDrawImage final : public OptBase
{
public:
    OptDrawImage(MEngine::Scene* scene);
    ~OptDrawImage();

public:
    virtual void enter();
    virtual void exit();

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:

    QString m_strImgPath;

    unsigned char* m_imageData = nullptr;

    int m_imgW = 0;
    int m_imgH = 0;
    int m_imgCh = 0;
};

#endif // OPTDRAWIMAGE_H
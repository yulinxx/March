#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QWidget>
#include <QPoint>
#include <vector>
#include "def.h"
#include "Scene/Scene.h"
#include "Render/MarchView.h"

class OptBase;
class OptManager;

class ViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWrapper(QWidget* parent = nullptr);
    ~ViewWrapper();

public:
    const std::vector<MRender::ColorPoint>& getLinePoints() const;
    // float getScale() const;
    //QVector2D getTranslation() const;

public:
    MRender::MarchView* getGlView() const;
    MEngine::Scene* getScene();

    void updateRender();
    void updateScene();

    void setOperation(int nType);

signals:
    void sigCoordChanged(float x, float y); // 信号：鼠标坐标变化

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void resetView();

private:
    MRender::MarchView* m_glView{ nullptr };
    MEngine::Scene* m_scene{ nullptr };


    std::shared_ptr<OptManager> m_optManager = nullptr;
};

#endif // VIEWWRAPPER_H

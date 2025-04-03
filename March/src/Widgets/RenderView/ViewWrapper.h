#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QWidget>
#include <QPoint>
#include <vector>
#include "Scene/Scene.h"
#include "Render/MarchView.h"
#include "Operation/OptBase.h"

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

    void setOperation(std::shared_ptr<OptBase> operation);

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

    QPoint m_lastPos;

    qint64 m_lastMiddleClickTime = 0;// 中键点击时间
    QPoint m_lastMiddlePos;// 鼠标位置

    bool m_bPanning = false; // 是否平移
    QPoint m_lastPanPos; // 上次平移位置

    // 窗、交选
    bool m_bSelecting = false;
    Ut::Vec2d m_selectStart;
    Ut::Vec2d m_selectEnd;

    std::shared_ptr<OptBase> m_selectOpt = nullptr; 
    std::shared_ptr<OptBase> m_curOpt = nullptr;

};

#endif // VIEWWRAPPER_H

#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QWidget>
#include <QPoint>
#include <QVector>
#include <vector>
#include "Scene/Scene.h"
#include "Render/MarchView.h"

class ViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWrapper(QWidget* parent = nullptr);
    ~ViewWrapper();

public:
    const std::vector<MRender::ColorPoint>& getLinePoints() const;
    float getScale() const;
    QVector2D getTranslation() const;

public:
    MRender::MarchView* getGlView() const;
    MEngine::Scene* getScene();

    void updateScene();

    //public:
        //QPointF screenToNDC(const QPoint& screenPos) const;
        //QPointF screenToWorld(const QPoint& screenPos) const;
    //    QPointF ndcToWorld(float ndcX, float ndcY) const;
    //    QPointF worldToNDC(float worldX, float worldY) const;
    //    QPointF worldToScreen(float worldX, float worldY) const;
    //    QPointF ndcToScreen(float ndcX, float ndcY) const;

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
    void testCoordinateMapping(QPoint& pt);
    void resetView();

private:
    MRender::MarchView* m_glView{ nullptr };
    MEngine::Scene* m_scene{ nullptr };

    QPoint m_lastPos;

    qint64 m_lastMiddleClickTime = 0;// 中键点击时间
    QPoint m_lastMiddlePos;// 鼠标位置

    bool m_bPanning = false; // 是否平移
    //double m_dZoomFactor = 1.0; // 缩放因子

    QPoint m_lastPanPos; // 上次平移位置

    // 窗、交选
    bool m_bSelecting = false;
    Ut::Vec2d m_selectStart;
    Ut::Vec2d m_selectEnd;

};

#endif // VIEWWRAPPER_H

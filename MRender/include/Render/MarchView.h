#ifndef MARCHVIEW_H
#define MARCHVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <vector>
#include <QPainter>

#include "MRenderAPI.h"
#include "Ut/Matrix.h"

namespace MRender
{
    struct ColorPoint
    {
        float x, y, z;
        float r, g, b;
    };

    class MRENDER_API MarchView : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
    {
        Q_OBJECT

    public:
        explicit MarchView(QWidget* parent = nullptr);
        ~MarchView();

    public:
        void setViewMatrix(Ut::Mat3& mat);

        const std::vector<ColorPoint>& getLinePoints() const;
        //float getScale() const;
        QVector2D getTranslation() const;
        //void setScale(float scale);
        void setTranslation(const QVector2D& translation);

        void addLinePoint(const ColorPoint& point);

        void clearLinePoints();

    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
        void paintEvent(QPaintEvent* event) override;

        // protected:
        //     void mousePressEvent(QMouseEvent* event) override;
        //     void wheelEvent(QWheelEvent* event) override;
        //     void mouseMoveEvent(QMouseEvent* event) override;
        //     void keyPressEvent(QKeyEvent* event) override;

    private:
        void updateLineBuffer();
        void updateCrossBuffer();
        void updateRuler();

    private:
        QOpenGLShaderProgram* m_lineProgram{ nullptr };
        GLuint m_lineVao;
        GLuint m_lineVbo;

        //float m_scale = 1.0f;
        QVector2D m_translation;
        QPoint m_lastPos;

        std::vector<ColorPoint> m_linePoints;
        std::vector<ColorPoint> m_crossPoints;
        GLuint m_crossVao, m_crossVbo;
        QOpenGLShaderProgram* m_crossProgram;

        struct RulerLine
        {
            ColorPoint start;      // 标尺起点
            ColorPoint end;        // 标尺终点
            float worldValue; // 标尺的世界坐标值（用于文本显示）
        };

        std::vector<RulerLine> m_rulerLines;
        GLuint m_rulerVao, m_rulerVbo;
        QOpenGLShaderProgram* m_rulerProgram{ nullptr };

        Ut::Mat3 m_matView;
        QMatrix4x4 m_viewMatrix;
    };
}

#endif // MARCHVIEW_H
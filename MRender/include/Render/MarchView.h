#ifndef MARCHVIEW_H
#define MARCHVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
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

    class MRENDER_API MarchView : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
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
        void addLinesPoint(const ColorPoint& point);

        void addLinesData(const float* points, size_t sz);
        void addLinesIndex(const unsigned int* index, size_t sz);

        void addPreviewData(const float* points, size_t sz);
        void addPreviewIndex(const unsigned int* index, size_t sz);

        void clearLinePoints();
        void clearLinesPoints();

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

        void updateLinesDataBuffer();
        void updateLinesIndexBuffer();

        void updatePreviewDataBuffer();
        void updatePreviewIndexBuffer();

        void updateCrossBuffer();
        void updateRuler();

    private:
        // 单线段资源
        GLuint m_lineVao;
        GLuint m_lineVbo;
        QOpenGLShaderProgram* m_lineProgram{ nullptr };

        std::vector<ColorPoint> m_linePoints;

        // 多段线资源
        GLuint m_linesVao;
        GLuint m_linesVbo;
        GLuint m_linesEbo;
        QOpenGLShaderProgram* m_linesProgram{ nullptr };
        std::vector<float> m_vLinesPoints;
        std::vector<unsigned int> m_vLinesIndex;

        GLuint m_previewVao;
        GLuint m_previewVbo;
        GLuint m_previewEbo;
        QOpenGLShaderProgram* m_previewProgram{ nullptr };

        std::vector<float> m_vPreviewPoints;
        std::vector<unsigned int> m_vPreviewIndex;


        // Cross
        GLuint m_crossVao;
        GLuint m_crossVbo;
        QOpenGLShaderProgram* m_crossProgram{ nullptr };

        std::vector<ColorPoint> m_crossPoints;

        // Ruler
        struct RulerLine
        {
            ColorPoint start;      // 标尺起点
            ColorPoint end;        // 标尺终点
            float worldValue; // 标尺的世界坐标值（用于文本显示）
        };

        std::vector<RulerLine> m_rulerLines;
        GLuint m_rulerVao, m_rulerVbo;
        QOpenGLShaderProgram* m_rulerProgram{ nullptr };

        // Mat
        Ut::Mat3 m_matView;
        QMatrix4x4 m_viewMatrix;

        QVector2D m_translation;
        QPoint m_lastPos;
    };
}

#endif // MARCHVIEW_H
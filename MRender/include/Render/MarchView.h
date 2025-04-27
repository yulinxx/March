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

        void addLineData(const float* points, size_t sz);
        void addLinePreview(const float* points, size_t sz);

        void addLinesData(const float* points, size_t sz);
        void addLinesIndex(const unsigned int* index, size_t sz);

        void addPreviewData(const float* points, size_t sz);
        void addPreviewIndex(const unsigned int* index, size_t sz);

        void addImgPreviewData(unsigned char* imgData, int w, int h, int c = 3);

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
        void addRectData();

        void updateLineBuffer(); // 更新线段数据
        void updateLineDataBuffer(); // 线段
        void updateLinePreviewBuffer(); // 线段预览

        void updateLinesDataBuffer(); // 多线段
        void updateLinesIndexBuffer();

        void updatePreviewDataBuffer();
        void updatePreviewIndexBuffer();

        void updateCrossBuffer(); // 十字标
        void updateRuler(); // 标尺

        void updateImageBuffer(); // 位图

    private:
        // 单线段资源
        GLuint m_lineVao = 0;
        GLuint m_lineVbo = 0;
        QOpenGLShaderProgram* m_lineProgram{ nullptr };

        std::vector<float> m_vLinePoints;
        std::vector<ColorPoint> m_linePoints;

        std::vector<float> vRectPoints;

        GLuint m_linePreviewVao = 0;
        GLuint m_linePreviewVbo = 0;
        QOpenGLShaderProgram* m_linePreviewProgram{ nullptr };
        std::vector<float> m_vLinePreview;

        // 多段线资源
        GLuint m_linesVao = 0;
        GLuint m_linesVbo = 0;
        GLuint m_linesEbo = 0;
        QOpenGLShaderProgram* m_linesProgram{ nullptr };
        std::vector<float> m_vLinesPoints;
        std::vector<unsigned int> m_vLinesIndex;

        GLuint m_previewVao = 0;
        GLuint m_previewVbo = 0;
        GLuint m_previewEbo = 0;
        QOpenGLShaderProgram* m_previewProgram{ nullptr };

        std::vector<float> m_vPreviewPoints;
        std::vector<unsigned int> m_vPreviewIndex;

        // Cross
        GLuint m_crossVao = 0;
        GLuint m_crossVbo = 0;
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
        GLuint m_rulerVao = 0;
        GLuint m_rulerVbo = 0;
        QOpenGLShaderProgram* m_rulerProgram{ nullptr };

        // Image
        GLuint m_imageVao = 0;
        GLuint m_imageVbo = 0;
        GLuint m_imageTexture = 0;
        QOpenGLShaderProgram* m_imageProgram{ nullptr };

        unsigned char* m_imgData = nullptr;
        int m_imgWidth = 0;
        int m_imgHeight = 0;
        int m_imgChannels = 3;
        float m_imgX = 10.0f;
        float m_imgY = 10.0f;
        int m_imgW = 0;
        int m_imgH = 0;

        // Mat
        Ut::Mat3 m_matView;
        QMatrix4x4 m_viewMatrix;

        QVector2D m_translation;
        QPoint m_lastPos;
        size_t m_nIndex = 0;
    };
}

#endif // MARCHVIEW_H
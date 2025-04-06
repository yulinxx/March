#include "MarchView.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <cmath>
#include <random>
#include "Logger.h"

namespace MRender
{
    MarchView::MarchView(QWidget* parent)
        : QOpenGLWidget(parent)
    {
        QSurfaceFormat format;
        format.setVersion(4, 0);
        format.setProfile(QSurfaceFormat::CoreProfile);
        setFormat(format);

        setMouseTracking(true);

        m_crossPoints = {
            {-0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // 红色
            {0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},  // 红色
            {0.0f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f}, // 蓝色
            {0.0f, 0.9f, 0.0f, 0.0f, 0.0f, 1.0f},  // 蓝色
        };
    }

    MarchView::~MarchView()
    {
        makeCurrent();
        glDeleteVertexArrays(1, &m_lineVao);
        glDeleteBuffers(1, &m_lineVbo);
        delete m_lineProgram;

        glDeleteVertexArrays(1, &m_linesVao);
        glDeleteBuffers(1, &m_linesVbo);
        delete m_linesProgram;

        glDeleteVertexArrays(1, &m_crossVao);
        glDeleteBuffers(1, &m_crossVbo);
        delete m_crossProgram;

        glDeleteVertexArrays(1, &m_rulerVao);
        glDeleteBuffers(1, &m_rulerVbo);
        delete m_rulerProgram;

        doneCurrent();
    }

    void MarchView::initializeGL()
    {
        if (!initializeOpenGLFunctions())
        {
            qFatal("Could not initialize OpenGL 4.0 functions");
        }

        // Line
        const char* lineVS = R"(
            #version 400
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec3 color;
            uniform mat4 projection;
            uniform vec2 translation;
            uniform float scale = 1.0;
            out vec3 fragColor;
            void main()
            {
                vec3 scaledPos = vec3(position.xy * scale + translation, position.z);
                gl_Position = projection * vec4(scaledPos, 1.0);
                fragColor = color;
            }
        )";

        const char* lineFS = R"(
            #version 400
            in vec3 fragColor;
            out vec4 outColor;
            void main()
            {
                outColor = vec4(fragColor, 1.0);
            }
        )";

        {

            m_lineProgram = new QOpenGLShaderProgram(this);;
            m_lineProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, lineVS);
            m_lineProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, lineFS);
            m_lineProgram->link();

            glGenVertexArrays(1, &m_lineVao);
            glGenBuffers(1, &m_lineVbo);
            glBindVertexArray(m_lineVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        // 初始化lines program
        {
            m_linesProgram = new QOpenGLShaderProgram(this);
            m_linesProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, lineVS);
            m_linesProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, lineFS);
            m_linesProgram->link();
            
            // glGenVertexArrays(1, &m_linesVao);
            // glGenBuffers(1, &m_linesVbo);
            glGenVertexArrays(1, &m_linesVao);
            glGenBuffers(1, &m_linesVbo);
            glBindVertexArray(m_linesVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_linesVbo);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        // Cross
        {
            const char* crossVS = R"(
            #version 400
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec3 color;
            out vec3 fragColor;
            void main()
            {
                gl_Position = vec4(position, 1.0);
                fragColor = color;
            }
        )";

            const char* crossFS = R"(
            #version 400
            in vec3 fragColor;
            out vec4 outColor;
            void main()
            {
                outColor = vec4(fragColor, 1.0);
            }
        )";

            m_crossProgram = new QOpenGLShaderProgram;
            m_crossProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, crossVS);
            m_crossProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, crossFS);
            m_crossProgram->link();

            glGenVertexArrays(1, &m_crossVao);
            glGenBuffers(1, &m_crossVbo);
            glBindVertexArray(m_crossVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_crossVbo);

            glBufferData(GL_ARRAY_BUFFER, m_crossPoints.size() * sizeof(ColorPoint),
                m_crossPoints.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        // Ruler
        {
            const char* rulerVS = R"(
            #version 400
            layout(location = 0) in vec2 position;
            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
            }
        )";
            const char* rulerFS = R"(
            #version 400
            out vec4 fragColor;
            void main()
            {
                fragColor = vec4(0.0, 0.0, 1.0, 1.0); // 蓝色标尺
            }
        )";

            m_rulerProgram = new QOpenGLShaderProgram;
            m_rulerProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, rulerVS);
            m_rulerProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, rulerFS);
            m_rulerProgram->link();

            glGenVertexArrays(1, &m_rulerVao);
            glGenBuffers(1, &m_rulerVbo);
            glBindVertexArray(m_rulerVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_rulerVbo);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        clearLinePoints();
        updateRuler();
    }

    void MarchView::resizeGL(int w, int h)
    {
        glViewport(0, 0, w, h);
        updateRuler();
    }

    void MarchView::paintGL()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float aspect = float(width()) / height();
        float orthoSize = 1000.0f;
        // QMatrix4x4 projection;
        // projection.ortho(-orthoSize * aspect, orthoSize * aspect,
        //     -orthoSize, orthoSize,
        //     -1.0f, 1.0f);

        if (m_linePoints.size() >= 2 && m_lineProgram->bind())
        {
            // m_lineProgram->setUniformValue("projection", projection);
            m_lineProgram->setUniformValue("projection", m_viewMatrix);
            m_lineProgram->setUniformValue("translation", m_translation);
            //m_lineProgram->setUniformValue("scale", m_scale);
            glBindVertexArray(m_lineVao);
            glEnable(GL_PRIMITIVE_RESTART);
            glDrawArrays(GL_LINES, 0, GLsizei(m_linePoints.size()));
            glDisable(GL_PRIMITIVE_RESTART);
            glBindVertexArray(0);
            m_lineProgram->release();
        }

        if (m_linesPoints.size() >= 2 && m_linesProgram->bind())
        {
            m_linesProgram->setUniformValue("projection", m_viewMatrix);
            m_linesProgram->setUniformValue("translation", m_translation);
            //m_lineProgram->setUniformValue("scale", m_scale);
            glBindVertexArray(m_linesVao);
            glDrawArrays(GL_LINE_STRIP, 0, GLsizei(m_linesPoints.size()));
            glBindVertexArray(0);
            m_linesProgram->release();
        }

        if (m_crossPoints.size() >= 2 && m_crossProgram->bind())
        {
            glBindVertexArray(m_crossVao);
            glDrawArrays(GL_LINES, 0, GLsizei(m_crossPoints.size()));
            glBindVertexArray(0);
            m_crossProgram->release();
        }

        if (m_rulerLines.size() >= 1 && m_rulerProgram->bind())
        {
            glBindVertexArray(m_rulerVao);
            glDrawArrays(GL_LINES, 0, GLsizei(m_rulerLines.size() * 2));
            glBindVertexArray(0);
            m_rulerProgram->release();
        }
    }

    void MarchView::paintEvent(QPaintEvent* event)
    {
        QOpenGLWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QFont font("Arial", 8);
        painter.setFont(font);
        painter.setPen(Qt::black);

        for (const auto& line : m_rulerLines)
        {
            float screenX = (line.start.x + 1.0f) / 2.0f * width();
            float screenY = (1.0f - line.start.y) / 2.0f * height();

            if (line.start.y == line.end.y) // 垂直标尺
            {
                painter.drawText(screenX + 5, screenY, QString::number(line.worldValue, 'f', 1));
            }
            else // 水平标尺
            {
                painter.drawText(screenX - 10, screenY - 5, QString::number(line.worldValue, 'f', 1));
            }
        }

        painter.end();
    }

    // void MarchView::mousePressEvent(QMouseEvent *event)
    // {
    // }

    // void MarchView::wheelEvent(QWheelEvent *event)
    // {
    //     QOpenGLWidget::wheelEvent(event);
    // }

    // void MarchView::mouseMoveEvent(QMouseEvent *event)
    // {
    //     QOpenGLWidget::mouseMoveEvent(event);
    // }

    // void MarchView::keyPressEvent(QKeyEvent *event)
    // {
    //     QOpenGLWidget::keyPressEvent(event);
    // }

    void MarchView::setViewMatrix(Ut::Mat3& mat)
    {
        m_matView = mat;

        m_viewMatrix.setToIdentity();
        m_viewMatrix(0, 0) = mat(0, 0);
        m_viewMatrix(0, 1) = mat(0, 1);
        m_viewMatrix(0, 3) = mat(0, 2);
        m_viewMatrix(1, 0) = mat(1, 0);
        m_viewMatrix(1, 1) = mat(1, 1);
        m_viewMatrix(1, 3) = mat(1, 2);
        m_viewMatrix(2, 2) = mat(2, 2);
        m_viewMatrix(3, 3) = 1.0f;

        // qDebug() << "\n------------\n";
        // qDebug() << "Mat3:" << mat(0, 0) << mat(0, 1) << mat(0, 2);
        // qDebug() << "     " << mat(1, 0) << mat(1, 1) << mat(1, 2);
        // qDebug() << "     " << mat(2, 0) << mat(2, 1) << mat(2, 2);

        // qDebug() << "\nQMatrix4x4:\n" << m_viewMatrix;

        update();
    }

    void MarchView::updateLineBuffer()
    {
        glBindVertexArray(m_lineVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
        if (m_linePoints.empty())
        {
            glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t bufferSize = m_linePoints.size() * sizeof(ColorPoint);
            if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nBufferSz = static_cast<GLsizei>(bufferSize);
            glBufferData(GL_ARRAY_BUFFER, nBufferSz, m_linePoints.data(), GL_STATIC_DRAW);
        }
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MarchView::updateLinesBuffer()
    {
        glBindVertexArray(m_linesVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_linesVbo);
        if (m_linesPoints.empty())
        {
            glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t bufferSize = m_linesPoints.size() * sizeof(ColorPoint);
            if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nBufferSz = static_cast<GLsizei>(bufferSize);
            glBufferData(GL_ARRAY_BUFFER, nBufferSz, m_linesPoints.data(), GL_STATIC_DRAW);
        }
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MarchView::updateCrossBuffer()
    {
        glBindVertexArray(m_crossVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_crossVbo);
        size_t bufferSize = m_crossPoints.size() * sizeof(ColorPoint);
        if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
        {
            qWarning() << "Buffer size exceeds GLsizei limit";
            return;
        }
        GLsizei nBufferSz = static_cast<GLsizei>(bufferSize);
        glBufferData(GL_ARRAY_BUFFER, nBufferSz, m_crossPoints.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MarchView::updateRuler()
    {
        return;
        m_rulerLines.clear();
        m_rulerLines.shrink_to_fit();

        // 计算当前视图的世界坐标范围
        float aspect = float(width()) / height();
        float orthoSize = 1000.0f;
        //float viewWidth = orthoSize * aspect * 2.0f / m_scale;
        //float viewHeight = orthoSize * 2.0f / m_scale;
        float viewWidth = orthoSize * aspect * 2.0f;
        float viewHeight = orthoSize * 2.0f;

        float left = -viewWidth / 2.0f + m_translation.x();
        float right = viewWidth / 2.0f + m_translation.x();
        float bottom = -viewHeight / 2.0f + m_translation.y();
        float top = viewHeight / 2.0f + m_translation.y();

        // 计算标尺步长
        float step = pow(10.0f, floor(log10(viewWidth / 10.0f)));
        if (viewWidth / step > 20)
            step *= 2.0f;

        // 生成水平标尺（固定在屏幕底部，沿 X 轴）
        float rulerHeight = 0.1f; // 固定高度（NDC 单位）
        float baseY = -1.0f;      // 屏幕底部（NDC）
        for (float x = floor(left / step) * step; x <= right; x += step)
        {
            // 计算 NDC X 坐标
            float ndcX = (x - left) / (right - left) * 2.0f - 1.0f;
            if (ndcX >= -1.0f && ndcX <= 1.0f) // 只绘制可见范围内的标尺
            {
                ColorPoint start = { ndcX, baseY, 0.0f, 0.0f, 0.0f, 0.0f };
                ColorPoint end = { ndcX, baseY + rulerHeight, 0.0f, 0.0f, 0.0f, 0.0f };
                m_rulerLines.push_back({ start, end, x }); // worldValue 为世界坐标值
            }
        }

        // 生成垂直标尺（固定在屏幕左侧，沿 Y 轴）
        float rulerWidth = 0.1f; // 固定宽度（NDC 单位）
        float baseX = -1.0f;     // 屏幕左侧（NDC）
        for (float y = floor(bottom / step) * step; y <= top; y += step)
        {
            // 计算 NDC Y 坐标
            float ndcY = (y - bottom) / (top - bottom) * 2.0f - 1.0f;
            if (ndcY >= -1.0f && ndcY <= 1.0f) // 只绘制可见范围内的标尺
            {
                ColorPoint start = { baseX, ndcY, 0.0f, 0.0f, 0.0f, 0.0f };
                ColorPoint end = { baseX + rulerWidth, ndcY, 0.0f, 0.0f, 0.0f, 0.0f };
                m_rulerLines.push_back({ start, end, y }); // worldValue 为世界坐标值
            }
        }

        // 更新 VBO
        std::vector<float> rulerPoints;
        for (const auto& line : m_rulerLines)
        {
            rulerPoints.push_back(line.start.x);
            rulerPoints.push_back(line.start.y);
            rulerPoints.push_back(line.end.x);
            rulerPoints.push_back(line.end.y);
        }

        glBindVertexArray(m_rulerVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_rulerVbo);
        size_t bufferSize = rulerPoints.size() * sizeof(float);
        if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
        {
            qWarning() << "Buffer size exceeds GLsizei limit";
            return;
        }
        GLsizei bufferSizeRuler = static_cast<GLsizei>(bufferSize);
        glBufferData(GL_ARRAY_BUFFER, bufferSizeRuler, rulerPoints.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    const std::vector<ColorPoint>& MarchView::getLinePoints() const
    {
        return m_linePoints;
    }

    QVector2D MarchView::getTranslation() const
    {
        return m_translation;
    }

    void MarchView::setTranslation(const QVector2D& translation)
    {
        m_translation = translation;
        updateRuler();
    }

    void MarchView::addLinePoint(const ColorPoint& point)
    {
        m_linePoints.push_back(point);
        updateLineBuffer();
    }

    void MarchView::addLinesPoint(const ColorPoint& point)
    {
        m_linesPoints.push_back(point);
        updateLinesBuffer();
    }

    void MarchView::clearLinePoints()
    {
        m_linePoints.clear();
        m_linePoints.shrink_to_fit();

        // 添加矩形的四个顶点
        ColorPoint redColor = { 1.0f, 0.0f, 0.0f };

        // 定义一个结构体来存储矩形的坐标
        struct RectangleCoords
        {
            float x1 = 10.0f;
            float y1 = 10.0f;
            float x2 = 800.0f;
            float y2 = 800.0f;
        };

        const RectangleCoords rect = { 10.0f, 10.0f, 800.0f, 800.0f };

        // 第一条边: (x1, y1) 到 (x2, y1)
        m_linePoints.push_back({ rect.x1, rect.y1, 0.0f, redColor.r, redColor.g, redColor.b });
        m_linePoints.push_back({ rect.x2, rect.y1, 0.0f, redColor.r, redColor.g, redColor.b });

        // 第二条边: (x2, y1) 到 (x2, y2)
        m_linePoints.push_back({ rect.x2, rect.y1, 0.0f, redColor.r, redColor.g, redColor.b });
        m_linePoints.push_back({ rect.x2, rect.y2, 0.0f, redColor.r, redColor.g, redColor.b });

        // 第三条边: (x2, y2) 到 (x1, y2)
        m_linePoints.push_back({ rect.x2, rect.y2, 0.0f, redColor.r, redColor.g, redColor.b });
        m_linePoints.push_back({ rect.x1, rect.y2, 0.0f, redColor.r, redColor.g, redColor.b });

        // 第四条边: (x1, y2) 到 (x1, y1)
        m_linePoints.push_back({ rect.x1, rect.y2, 0.0f, redColor.r, redColor.g, redColor.b });
        m_linePoints.push_back({ rect.x1, rect.y1, 0.0f, redColor.r, redColor.g, redColor.b });

        updateLineBuffer();
    }

    void MarchView::clearLinesPoints()
    {
        m_linesPoints.clear();
        m_linesPoints.shrink_to_fit();

        updateLinesBuffer();
    }
}
#include "MarchView.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <cmath>
#include <random>

#include "Logger.h"
#include "Shader/ShaderDef.h"

namespace MRender
{
#define _DEBUG_ false

    MarchView::MarchView(QWidget* parent)
        : QOpenGLWidget(parent)
    {
        QSurfaceFormat format;
        format.setVersion(4, 6);
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
        auto delFunc = [this](QOpenGLShaderProgram* p, GLuint vao, GLuint vbo, GLuint ebo = 0) {
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);
            if (ebo != 0)
            {
                glDeleteBuffers(1, &ebo);
            }
            delete p;
            };

        delFunc(m_lineProgram, m_lineVao, m_lineVbo);
        delFunc(m_linesProgram, m_linesVao, m_linesVbo, m_linesEbo);
        delFunc(m_previewProgram, m_previewVao, m_previewVbo, m_previewEbo);
        delFunc(m_crossProgram, m_crossVao, m_crossVbo);
        delFunc(m_rulerProgram, m_rulerVao, m_rulerVbo);

        doneCurrent();
    }

    void MarchView::initializeGL()
    {
        if (!initializeOpenGLFunctions())
        {
            qFatal("Could not initialize OpenGL 4.6 functions");
        }

        // Line
        {
            m_lineProgram = new QOpenGLShaderProgram(this);
            m_lineProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, lineVS);
            m_lineProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, lineFS);
            m_lineProgram->link();

            glGenVertexArrays(1, &m_lineVao);
            glGenBuffers(1, &m_lineVbo);
            glBindVertexArray(m_lineVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorPoint), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        // 初始化 Lines 和 Preview
        //{
        //    auto initLines = [this](QOpenGLShaderProgram*& p, GLuint& vao, GLuint& vbo, GLuint& ebo) {
        //        if (p)
        //            delete p;

        //        p = new QOpenGLShaderProgram(this);
        //        p->addShaderFromSourceCode(QOpenGLShader::Vertex, linesVS);
        //        p->addShaderFromSourceCode(QOpenGLShader::Fragment, linesFS);
        //        p->link();

        //        glGenVertexArrays(1, &vao);
        //        glGenBuffers(1, &vbo);
        //        glGenBuffers(1, &ebo);

        //        glBindVertexArray(vao);
        //        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        //        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
        //        glEnableVertexAttribArray(0);
        //        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        //        glEnableVertexAttribArray(1);

        //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        //        glBindVertexArray(0);
        //        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //        };

        //    initLines(m_linesProgram, m_linesVao, m_linesVbo, m_linesEbo);
        //    initLines(m_previewProgram, m_previewVao, m_previewVbo, m_previewEbo);
        //}

        {
            m_linesProgram = new QOpenGLShaderProgram(this);
            m_linesProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, linesVS);
            m_linesProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, linesFS);
            m_linesProgram->link();

            glGenVertexArrays(1, &m_linesVao);
            glGenBuffers(1, &m_linesVbo);
            glGenBuffers(1, &m_linesEbo);

            glBindVertexArray(m_linesVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_linesVbo);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_linesEbo);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        {
            m_previewProgram = new QOpenGLShaderProgram(this);
            m_previewProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, linesVS);
            m_previewProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, linesFS);
            m_previewProgram->link();

            glGenVertexArrays(1, &m_previewVao);
            glGenBuffers(1, &m_previewVbo);
            glGenBuffers(1, &m_previewEbo);

            glBindVertexArray(m_previewVao);
            glBindBuffer(GL_ARRAY_BUFFER, m_previewVbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_previewEbo);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        // Cross
        {
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

        if (m_linePoints.size() >= 2 && m_lineProgram->bind())
        {
            m_lineProgram->setUniformValue("projection", m_viewMatrix);
            m_lineProgram->setUniformValue("translation", m_translation);
            glBindVertexArray(m_lineVao);
            glDrawArrays(GL_LINES, 0, GLsizei(m_linePoints.size()));
            glBindVertexArray(0);
            m_lineProgram->release();
        }

        if (m_vLinesPoints.size() >= 6 && m_linesProgram->bind())
        {
            m_linesProgram->setUniformValue("projection", m_viewMatrix);
            m_linesProgram->setUniformValue("translation", m_translation);

            glBindVertexArray(m_linesVao);
            glEnable(GL_PRIMITIVE_RESTART);
            glPrimitiveRestartIndex(std::numeric_limits<unsigned int>::max());
            glDrawElements(GL_LINE_STRIP, GLsizei(m_vLinesIndex.size()), GL_UNSIGNED_INT, 0);

            GLenum err = glGetError();
            if (err != GL_NO_ERROR)
            {
                qWarning() << "OpenGL error after drawing Lines:" << err;
            }

            glDisable(GL_PRIMITIVE_RESTART);
            glBindVertexArray(0);
            m_linesProgram->release();
        }

        if (m_vPreviewPoints.size() >= 6 && m_previewProgram->bind())
        {
            m_previewProgram->setUniformValue("projection", m_viewMatrix);
            m_previewProgram->setUniformValue("translation", m_translation);

            glBindVertexArray(m_previewVao);
            glEnable(GL_PRIMITIVE_RESTART);
            glPrimitiveRestartIndex(std::numeric_limits<unsigned int>::max());
            glDrawElements(GL_LINE_STRIP, GLsizei(m_vPreviewIndex.size()), GL_UNSIGNED_INT, 0);

            GLenum err = glGetError();
            if (err != GL_NO_ERROR)
            {
                qWarning() << "OpenGL error after drawing Preview:" << err;
            }

            glDisable(GL_PRIMITIVE_RESTART);
            glBindVertexArray(0);
            m_previewProgram->release();
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

    void MarchView::updateLinesDataBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_linesVbo);
        if (m_vLinesPoints.empty())
        {
            glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t bufferSize = m_vLinesPoints.size() * sizeof(float);
            if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nBufferSz = static_cast<GLsizei>(bufferSize);
            glBufferData(GL_ARRAY_BUFFER, nBufferSz, m_vLinesPoints.data(), GL_STATIC_DRAW);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void MarchView::updateLinesIndexBuffer()
    {
        glBindVertexArray(m_linesVao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_linesEbo);
        if (m_vLinesIndex.empty())
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t indexBufferSize = m_vLinesIndex.size() * sizeof(unsigned int);
            if (indexBufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Index buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nIndexBufferSz = static_cast<GLsizei>(indexBufferSize);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndexBufferSz, m_vLinesIndex.data(), GL_STATIC_DRAW);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void MarchView::updatePreviewDataBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_previewVbo);
        if (m_vPreviewPoints.empty())
        {
            glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t bufferSize = m_vPreviewPoints.size() * sizeof(float);
            if (bufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nBufferSz = static_cast<GLsizei>(bufferSize);
            glBufferData(GL_ARRAY_BUFFER, nBufferSz, m_vPreviewPoints.data(), GL_STATIC_DRAW);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void MarchView::updatePreviewIndexBuffer()
    {
        glBindVertexArray(m_previewVao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_previewEbo);
        if (m_vPreviewIndex.empty())
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
        }
        else
        {
            size_t indexBufferSize = m_vPreviewIndex.size() * sizeof(unsigned int);
            if (indexBufferSize > static_cast<size_t>(std::numeric_limits<GLsizei>::max()))
            {
                qWarning() << "Index buffer size exceeds GLsizei limit";
                return;
            }
            GLsizei nIndexBufferSz = static_cast<GLsizei>(indexBufferSize);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndexBufferSz, m_vPreviewIndex.data(), GL_STATIC_DRAW);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
        // m_linePoints.push_back(point);
        // updateLineBuffer();
    }

    void MarchView::addLinesPoint(const ColorPoint& point)
    {
        // m_linesPoints.push_back(point);
        // updateLinesDataBuffer();
    }

    void MarchView::addLinesData(const float* points, size_t sz)
    {
        if (sz < 2) return;
        if (sz % 6 != 0)
        {
            qWarning() << "addLinesData: sz must be a multiple of 6, got" << sz;
            return;
        }

        m_vLinesPoints.clear();
        m_vLinesPoints.resize(sz);
        memcpy(m_vLinesPoints.data(), points, sz * sizeof(float));
        updateLinesDataBuffer();

#if _DEBUG_
        // 调试：打印数据
        qDebug() << "m_vLinesPoints size:" << m_vLinesPoints.size();
        for (size_t i = 0; i < m_vLinesPoints.size(); i += 6)
        {
            qDebug() << "Vertex" << i / 6 << ": (" << m_vLinesPoints[i] << ","
                << m_vLinesPoints[i + 1] << "," << m_vLinesPoints[i + 2]
                << "), Color: (" << m_vLinesPoints[i + 3] << "," << m_vLinesPoints[i + 4]
                << "," << m_vLinesPoints[i + 5] << ")";
        }
#endif
    }

    void MarchView::addLinesIndex(const unsigned int* index, size_t sz)
    {
        if (sz < 2) return;

        m_vLinesIndex.clear();
        m_vLinesIndex.resize(sz);
        memcpy(m_vLinesIndex.data(), index, sz * sizeof(unsigned int));

        // 检查索引范围
#if _DEBUG_
        unsigned int maxIndex = static_cast<unsigned int>(m_vLinesPoints.size() / 6);
        for (size_t i = 0; i < sz; i++)
        {
            if (m_vLinesIndex[i] != std::numeric_limits<unsigned int>::max() && m_vLinesIndex[i] >= maxIndex)
            {
                qWarning() << "Lines Index out of range: index =" << m_vLinesIndex[i] << ", maxIndex =" << maxIndex;
                return;
            }
        }
#endif

        updateLinesIndexBuffer();

#if _DEBUG_
        // 调试：打印索引
        qDebug() << "m_vLinesIndex size:" << m_vLinesIndex.size();
        for (size_t i = 0; i < m_vLinesIndex.size(); i++)
        {
            qDebug() << "Index" << i << ":" << m_vLinesIndex[i];
        }
#endif
    }

    void MarchView::addPreviewData(const float* points, size_t sz)
    {
        if (sz < 2) return;
        if (sz % 6 != 0)
        {
            qWarning() << "addPreviewData: sz must be a multiple of 6, got" << sz;
            return;
        }

        m_vPreviewPoints.clear();
        m_vPreviewPoints.resize(sz);
        memcpy(m_vPreviewPoints.data(), points, sz * sizeof(float));
        updatePreviewDataBuffer();

#if _DEBUG_
        // 调试：打印数据
        qDebug() << "m_vPreviewPoints size:" << m_vPreviewPoints.size();
        for (size_t i = 0; i < m_vPreviewPoints.size(); i += 6)
        {
            qDebug() << "Vertex" << i / 6 << ": (" << m_vPreviewPoints[i] << ","
                << m_vPreviewPoints[i + 1] << "," << m_vPreviewPoints[i + 2] << "), Color: ("
                << m_vPreviewPoints[i + 3] << "," << m_vPreviewPoints[i + 4]
                << "," << m_vPreviewPoints[i + 5] << ")";
        }
#endif
    }

    void MarchView::addPreviewIndex(const unsigned int* index, size_t sz)
    {
        if (sz < 2) return;

        m_vPreviewIndex.clear();
        m_vPreviewIndex.resize(sz);
        memcpy(m_vPreviewIndex.data(), index, sz * sizeof(unsigned int));

        // 检查索引范围
        unsigned int maxIndex = static_cast<unsigned int>(m_vPreviewPoints.size() / 6);
        for (size_t i = 0; i < sz; i++)
        {
            if (m_vPreviewIndex[i] != std::numeric_limits<unsigned int>::max() && m_vPreviewIndex[i] >= maxIndex)
            {
                qWarning() << "Preview Index out of range: index =" << m_vPreviewIndex[i] << ", maxIndex =" << maxIndex;
                return;
            }
        }

        updatePreviewIndexBuffer();

#if _DEBUG_
        // 调试：打印索引
        qDebug() << "m_vPreviewIndex size:" << m_vPreviewIndex.size();
        for (size_t i = 0; i < m_vPreviewIndex.size(); i++)
        {
            qDebug() << "Index" << i << ":" << m_vPreviewIndex[i];
        }
#endif
    }

    void MarchView::clearLinePoints()
    {
        m_linePoints.clear();
        // m_linePoints.shrink_to_fit();

        return;

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
        m_vLinesPoints.clear();
        m_vLinesIndex.clear();
        m_vPreviewPoints.clear();
        m_vPreviewIndex.clear();

        updateLinesDataBuffer();
        updateLinesIndexBuffer();
        updatePreviewDataBuffer();
        updatePreviewIndexBuffer();
    }
}
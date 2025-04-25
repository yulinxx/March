#include "OptDrawImage.h"
#include <QFileDialog>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OptDrawImage::OptDrawImage(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Image;
    m_imageData = nullptr;
    m_imgW = 0;
    m_imgH = 0;
    m_imgCh = 0;
}

OptDrawImage::~OptDrawImage()
{
    if (m_imageData)
    {
        stbi_image_free(m_imageData);
    }
}

void OptDrawImage::enter()
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        QObject::tr("Open Image File"),
        "",
        QObject::tr("Image Files (*.jpg *.jpeg *.png *.bmp *.tga);;All Files (*.*)")
    );

    if (!fileName.isEmpty())
    {
        if (m_imageData)
        {
            stbi_image_free(m_imageData);
            m_imageData = nullptr;
        }

        m_imageData = stbi_load(fileName.toStdString().c_str(),
            &m_imgW,
            &m_imgH,
            &m_imgCh,
            0);

        if (!m_imageData)
        {
            // Handle error
            return;
        }
    }
}

void OptDrawImage::exit()
{

}


void OptDrawImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_imageData)
    {
        QPointF pos = event->pos();
        // 这里添加渲染逻辑，使用m_imageData和pos
        // 例如: renderImage(pos, m_imageData, m_imgW, m_imgH);
    }
}

void OptDrawImage::mouseReleaseEvent(QMouseEvent* event)
{
}

void OptDrawImage::mouseMoveEvent(QMouseEvent* event)
{
}

void OptDrawImage::wheelEvent(QWheelEvent* event)
{
}

void OptDrawImage::keyPressEvent(QKeyEvent* event)
{
}
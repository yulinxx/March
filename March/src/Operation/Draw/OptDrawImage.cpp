#include "OptDrawImage.h"
#include <QFileDialog>
#include "Eng/Entity/Image.h"

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
    m_strImgPath = "";

    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        QObject::tr("Open Image File"),
        "",
        QObject::tr("Image Files (*.jpg *.jpeg *.png *.bmp *.tga);;All Files (*.*)")
    );

    if (!fileName.isEmpty())
    {
        m_strImgPath = fileName;

        // if (m_imageData)
        // {
        //     stbi_image_free(m_imageData);
        //     m_imageData = nullptr;
        // }

        // m_imageData = stbi_load(fileName.toStdString().c_str(),
        //     &m_imgW,
        //     &m_imgH,
        //     &m_imgCh,
        //     0);

        // if (!m_imageData)
        // {
        //     // Handle error
        //     return;
        // }
    }
}

void OptDrawImage::exit()
{

}

void OptDrawImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        auto wPos = m_scene->screenToWorld({ pos.x(), pos.y() });

        MEngine::Image* img = new MEngine::Image();
        img->loadFromFile(m_strImgPath.toStdString().c_str());

        img->setPosition(wPos);

        auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, img);
        m_scene->execute(std::move(addCmd));

        m_viewWrap->updateRender();
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
#include "OptDrawImage.h"
#include <QFileDialog>
#include "Eng/Entity/Image.h"

#include "Ut/tools.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

OptDrawImage::OptDrawImage(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Image;
    //m_imageData = nullptr;
    //m_imgW = 0;
    //m_imgH = 0;
    //m_imgCh = 0;
}

OptDrawImage::~OptDrawImage()
{
    //if (m_imageData)
    //{
    //    stbi_image_free(m_imageData);
    //}
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

        MEngine::Image* img = new MEngine::Image();
        img->loadFromFile(m_strImgPath.toStdString().c_str());

        int imgW= img->getWidth();
        int imgH= img->getHeight();
        double w = Ut::pxToMm(imgW);
        double h = Ut::pxToMm(imgH);

        w /= 2.0;
        h /= 2.0;

        //img->setSize({ w, h });


        //m_imgCh = 4; // 假设图像通道数为4，即RGBA

        Ut::Vec2d sz = m_viewWrap->getScene()->getViewSize();

        // 视图中心点坐标
        Ut::Vec2d centerPos = m_scene->getViewCenter();

        img->setPosition({ centerPos.x() - w, centerPos.y() - h});
        //img->setSize({ w, h });

        auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, img);
        m_scene->execute(std::move(addCmd));
        m_viewWrap->updateRender();

    }
}

void OptDrawImage::exit()
{
}

void OptDrawImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {

    }

    Super::mousePressEvent(event);
}

void OptDrawImage::mouseReleaseEvent(QMouseEvent* event)
{
    Super::mouseReleaseEvent(event);
}

void OptDrawImage::mouseMoveEvent(QMouseEvent* event)
{
    Super::mouseMoveEvent(event);
}

void OptDrawImage::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawImage::keyPressEvent(QKeyEvent* event)
{
    Super::keyPressEvent(event);
}
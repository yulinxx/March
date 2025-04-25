void GLView::render()
{
    // ... existing line rendering code ...
    
    // 渲染图像
    auto pairImageData = m_scene->getDrawData()->getImageData();
    float* ptImages = pairImageData.first;
    size_t szImages = pairImageData.second;
    
    if (szImages > 0)
    {
        m_glRenderer->addImageData(ptImages, szImages);
    }
}
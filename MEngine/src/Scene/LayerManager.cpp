#include "Scene/Layer/LayerManager.h"

namespace MEngine
{

    struct LayerManager::Impl
    {
        size_t nCurrent = 0;
        std::vector<std::shared_ptr<Layer>> vLayers;
    };


    LayerManager::LayerManager() : pImpl(std::make_shared<Impl>())
    {
        setCurrentLayer(0xFF000000);
    }

    LayerManager::~LayerManager() = default;

    Layer* LayerManager::setCurrentLayer(int nColor /*=0xFF000000*/)
    {
        for (auto& layer : pImpl->vLayers)
        {
            if (layer->getColor() == nColor)
                return layer.get();
        }

        //if (pImpl->vLayers.empty())
        {
            auto newLayer = std::make_shared<Layer>();
            pImpl->vLayers.push_back(newLayer);
            pImpl->nCurrent = 0; // 设置当前图层索引为 0
            return newLayer.get();
        }
    }


    void LayerManager::addEntity(std::shared_ptr<Entity> entity)
    {
        getCurrentLayer()->addEntity(entity);
    }


    void LayerManager::removeEntity(std::shared_ptr<Entity> entity)
    {
        getCurrentLayer()->removeEntity(entity);
    }

    Layer* LayerManager::addLayer()
    {
        auto newLayer = std::make_shared<Layer>();
        pImpl->vLayers.push_back(newLayer);
        return newLayer.get();
    }

    Layer* LayerManager::addLayer(Layer* layer)
    {
        if (layer)
        {
            pImpl->vLayers.push_back(std::shared_ptr<Layer>(layer));
            return pImpl->vLayers.back().get();
        }
        return nullptr;
    }

    Layer* LayerManager::getCurrentLayer()
    {
        if (pImpl->vLayers.empty())
            return setCurrentLayer();

        return pImpl->vLayers[pImpl->nCurrent].get();
    }

    Layer* LayerManager::getIndexLayer(size_t n)
    {
        if (pImpl->vLayers.empty())
            return setCurrentLayer();

        if (n >= pImpl->vLayers.size())
            n = pImpl->vLayers.size() - 1;

        return pImpl->vLayers[n].get();
    }

    // 根据名称获取图层
    Layer* LayerManager::getIndexLayer(char* name)
    {
        // if (name)
        // {
        //     std::string layerName(name);
        //     for (const auto& layer : pImpl->vLayers)
        //     {
        //         if (layer->getName() == layerName)
        //         {
        //             return layer.get();
        //         }
        //     }
        // }
        return nullptr;
    }
    const void LayerManager::getLayers(std::vector<std::shared_ptr<Layer>>& vLayers) const
    {
        vLayers.insert(vLayers.begin(), pImpl->vLayers.begin(), pImpl->vLayers.end());
    }
    void LayerManager::cleanupInactiveLayers()
    {
        for (auto it = pImpl->vLayers.begin(); it != pImpl->vLayers.end(); )
        {
            if (!(*it)->isActive())
            {
                it = pImpl->vLayers.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }



}



#if 0


1. 基本颜色
这些是常见的纯色，广泛用于界面设计和绘图。

颜色名称	RGB(R, G, B)	十六进制(0xAARRGGBB)	描述
黑色(Black)	(0, 0, 0)	0xFF000000	纯黑
白色(White)	(255, 255, 255)	0xFFFFFFFF	纯白
红色(Red)	(255, 0, 0)	0xFFFF0000	纯红
绿色(Green)	(0, 255, 0)	0xFF00FF00	纯绿
蓝色(Blue)	(0, 0, 255)	0xFF0000FF	纯蓝
黄色(Yellow)	(255, 255, 0)	0xFFFFFF00	纯黄
青色(Cyan)	(0, 255, 255)	0xFF00FFFF	青色（蓝绿）
品红(Magenta)	(255, 0, 255)	0xFFFF00FF	品红（紫红）
2. 深色变体
这些是基本颜色的较暗版本，常用于背景或阴影。

颜色名称	RGB(R, G, B)	十六进制(0xAARRGGBB)	描述
深红(Dark Red)	(139, 0, 0)	0xFF8B0000	暗红色
深绿(Dark Green)	(0, 100, 0)	0xFF006400	暗绿色
深蓝(Dark Blue)	(0, 0, 139)	0xFF00008B	暗蓝色
深黄(Dark Yellow)	(139, 139, 0)	0xFF8B8B00	暗黄色（橄榄色）
深青(Dark Cyan)	(0, 139, 139)	0xFF008B8B	暗青色
深品红(Dark Magenta)	(139, 0, 139)	0xFF8B008B	暗品红色
3. 浅色与灰色系
这些颜色柔和，常用于高亮、背景或中性色调。

颜色名称	RGB(R, G, B)	十六进制(0xAARRGGBB)	描述
浅灰(Light Gray)	(211, 211, 211)	0xFFD3D3D3	浅灰色
中灰(Gray)	(128, 128, 128)	0xFF808080	中等灰色
深灰(Dark Gray)	(105, 105, 105)	0xFF696969	深灰色
银色(Silver)	(192, 192, 192)	0xFFC0C0C0	金属银色
4. 实用颜色
这些颜色在设计中非常实用，例如警告色、强调色等。

颜色名称	RGB(R, G, B)	十六进制(0xAARRGGBB)	描述
橙色(Orange)	(255, 165, 0)	0xFFFFA500	鲜艳橙色
紫色(Purple)	(128, 0, 128)	0xFF800080	深紫色
粉色(Pink)	(255, 192, 203)	0xFFFFC0CB	浅粉色
棕色(Brown)	(165, 42, 42)	0xFFA52A2A	深棕色
金色(Gold)	(255, 215, 0)	0xFFFFD700	金黄色
天蓝(Sky Blue)	(135, 206, 235)	0xFF87CEEB	清新蓝色

#endif
#include "Scene/Layer/LayerManager.h"
#include <unordered_map>

namespace MEngine
{
    struct LayerManager::Impl
    {
        Layer* pCurrent = nullptr;
        std::unordered_map<size_t, std::shared_ptr<Layer>> m_Layers;
        size_t m_nNextId = 1;
    };

    LayerManager::LayerManager() : pImpl(std::make_shared<Impl>())
    {
        setCurrentLayer(0xFF000000);
    }

    LayerManager::~LayerManager() = default;

    Layer* LayerManager::setCurrentLayer(unsigned int nColor)
    {
        for (auto& [id, layer] : pImpl->m_Layers)
        {
            if (layer->getColor() == nColor)
            {
                pImpl->pCurrent = layer.get();
                return pImpl->pCurrent;
            }
        }

        auto newLayer = std::make_shared<Layer>();
        newLayer->setColor(nColor);

        size_t newId = pImpl->m_nNextId++;
        pImpl->m_Layers[newId] = newLayer;
        pImpl->pCurrent = newLayer.get();
        return pImpl->pCurrent;
    }

    void LayerManager::addEntity(std::shared_ptr<Entity> entity)
    {
        if (pImpl->pCurrent)
            pImpl->pCurrent->addEntity(entity);
    }

    void LayerManager::removeEntity(std::shared_ptr<Entity> entity)
    {
        if (pImpl->pCurrent)
            pImpl->pCurrent->removeEntity(entity);
    }

    Layer* LayerManager::addLayer()
    {
        auto newLayer = std::make_shared<Layer>();
        size_t newId = pImpl->m_nNextId++;
        pImpl->m_Layers[newId] = newLayer;
        pImpl->pCurrent = newLayer.get();
        return pImpl->pCurrent;
    }

    Layer* LayerManager::addLayer(Layer* layer)
    {
        if (layer)
        {
            size_t newId = pImpl->m_nNextId++;
            pImpl->m_Layers[newId] = std::shared_ptr<Layer>(layer);
            pImpl->pCurrent = layer;
            return layer;
        }
        return nullptr;
    }

    Layer* LayerManager::getCurrentLayer()
    {
        if (!pImpl->pCurrent && !pImpl->m_Layers.empty())
            pImpl->pCurrent = pImpl->m_Layers.begin()->second.get();
        return pImpl->pCurrent;
    }

    //Layer* LayerManager::getLayerById(size_t id)
    //{
    //    auto it = pImpl->m_Layers.find(id);
    //    return it != pImpl->m_Layers.end() ? it->second.get() : nullptr;
    //}

    void LayerManager::cleanupInactiveLayers()
    {
        for (auto it = pImpl->m_Layers.begin(); it != pImpl->m_Layers.end(); )
        {
            if (!it->second->isActive())
            {
                if (pImpl->pCurrent == it->second.get())
                    pImpl->pCurrent = nullptr;
                it = pImpl->m_Layers.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        if (!pImpl->pCurrent && !pImpl->m_Layers.empty())
            pImpl->pCurrent = pImpl->m_Layers.begin()->second.get();
    }
}
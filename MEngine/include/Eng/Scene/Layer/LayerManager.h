#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <vector>
#include <memory>

#include "Scene/SceneComponent.h"
#include "Scene/Layer/Layer.h"

namespace MEngine
{
    class MENGINE_API LayerManager : public SceneComponent
    {
    public:
        LayerManager();
        ~LayerManager();

    public:
        virtual void addEntity(std::shared_ptr<Entity> entity) override;
        virtual void removeEntity(std::shared_ptr<Entity> entity) override;

    public:
        // 添加图层
        Layer* setCurrentLayer(unsigned int nColor = 0xFF000000); // 默认黑色

        Layer* addLayer();
        Layer* addLayer(Layer* layer);

        Layer* getCurrentLayer();
        //Layer* getIndexLayer(size_t n);
        //Layer* getIndexLayer(char* name);

        // 获取所有图层
        //const void getLayers(std::vector<std::shared_ptr<Layer>>& vLayers) const;

    private:
        // 删除不活跃的图层
        void cleanupInactiveLayers();

    private:
        struct Impl;
        std::shared_ptr<Impl> pImpl;
    };
}

#endif // LAYERMANAGER_H
#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <vector>
#include <memory>
#include "Layer.h"

class LayerManager {
public:
    // 添加图层
    Layer* addLayer(int order, int color) {
        layers_.push_back(std::make_unique<Layer>(order, color));
        return layers_.back().get();
    }

    // 删除不活跃的图层
    void cleanupInactiveLayers() {
        for (auto it = layers_.begin(); it != layers_.end(); ) {
            if (!(*it)->isActive()) {
                it = layers_.erase(it);
            } else {
                ++it;
            }
        }
    }

    // 获取所有图层
    const std::vector<std::unique_ptr<Layer>>& getLayers() const {
        return layers_;
    }

private:
    std::vector<std::unique_ptr<Layer>> layers_;
};

#endif // LAYERMANAGER_H
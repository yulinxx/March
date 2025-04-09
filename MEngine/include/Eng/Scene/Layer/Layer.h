#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include <string>
#include "MEngineAPI.h"

namespace MEngine
{
    class Entity;

    class MENGINE_API Layer
    {
    public:
        Layer(const std::string& name, int order, int color);
        ~Layer();

    public:
        // 添加图元
        void addEntity(std::shared_ptr<Entity> entity);

        // 删除图元
        void removeEntity(std::shared_ptr<Entity> entity);

        // 设置锁定状态
        void setLocked(bool locked);

        // 设置可见状态
        void setVisible(bool visible);

        // 设置处理状态
        void setProcessing(bool processing);

        // 获取图层名称
        const std::string& getName() const;

        // 获取图层顺序
        int getOrder() const;

        // 获取图层颜色
        int getColor() const;

        // 检查图层是否活跃
        bool isActive() const;

        // 检查图层是否锁定
        bool isLocked() const;

        // 检查图层是否可见
        bool isVisible() const;

        // 检查图层是否正在处理
        bool isProcessing() const;

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // LAYER_H
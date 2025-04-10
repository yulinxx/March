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
        Layer();
        Layer(const char* name, int order, int color);
        ~Layer();

    public:
        // 添加图元
        void addEntity(std::shared_ptr<Entity> entity);

        // 添加批量图元
        void addEntities(const std::vector<std::shared_ptr<Entity>>& entities);

        // 添加普通指针图元
        void addEntity(Entity* entity);

        // 添加普通指针批量图元
        void addEntities(const std::vector<Entity*>& entities);

        // 删除图元
        void removeEntity(std::shared_ptr<Entity> entity);

        // 删除批量图元
        void removeEntities(const std::vector<std::shared_ptr<Entity>>& entities);

        // 删除普通指针图元
        void removeEntity(Entity* entity);

        // 删除普通指针批量图元
        void removeEntities(const std::vector<Entity*>& entities);

        // 设置锁定状态
        void setLocked(bool locked);

        // 设置可见状态
        void setVisible(bool visible);

        // 设置处理状态
        void setProcessing(bool processing);

        // 获取图层名称
        const char* getName() const;

        // 获取图层顺序
        int getOrder() const;

        // 获取图层颜色
        int setColor(int color); // 设置整数颜色
        int setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255); // 设置 RGBA
        int getColor() const; // 获取整数颜色
        void getColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a = nullptr) const; // 获取 RGBA

        // 检查图层是否活跃
        bool isActive() const;

        // 检查图层是否锁定
        bool isLocked() const;

        // 检查图层是否可见
        bool isVisible() const;

        // 检查图层是否正在处理
        bool isProcessing() const;

    private:
        void init();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // LAYER_H
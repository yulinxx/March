#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "MEngineAPI.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

#include "Entity/Entity.h"
#include "MEngineAPI.h"
#include "Scene/SceneComponent.h"

namespace MEngine
{
    class MENGINE_API OrderManager final : public SceneComponent
    {
    public:
        OrderManager() = default;
        ~OrderManager() = default;

    public:
    public:
        virtual void addEntity(std::shared_ptr<Entity> entity) override;
        virtual void removeEntity(std::shared_ptr<Entity> entity) override;

        //// 添加图元到顺序列表
        //void addEntity(Entity* entity);

        //// 移除指定元素
        //bool removeEntity(Entity* entity);

        // 获取按顺序排列的图元列表
        std::vector<std::shared_ptr<Entity>>& getOrderedEntities();

        // 交换两个图元的顺序
        void swapEntities(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);

        // 移动图元到指定位置
        void moveEntityToPos(std::shared_ptr<Entity> entity, size_t position);

    private:
        std::unordered_map<std::shared_ptr<Entity>, size_t> m_mapEntIndex;
        std::vector<std::shared_ptr<Entity>> m_vOrderedEntities;

        // 按 m_nId 排序的比较函数
        static bool compareById(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
        {
            return a->getId() < b->getId();
        }
    };
}

#endif // ORDERMANAGER_H
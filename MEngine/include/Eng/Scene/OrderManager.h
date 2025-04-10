#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "MEngineAPI.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Entity/Entity.h"
#include "MEngineAPI.h"

namespace MEngine
{
    class MENGINE_API OrderManager final
    {
    public:
        OrderManager() = default;
        ~OrderManager() = default;

    public:
        // 添加图元到顺序列表
        void addEntity(Entity* entity);

        // 移除指定元素
        bool removeEntity(Entity* entity);

        // 获取按顺序排列的图元列表
        std::vector<Entity*>& getOrderedEntities();

        // 交换两个图元的顺序
        void swapEntities(Entity* entity1, Entity* entity2);

        // 移动图元到指定位置
        void moveEntityToPos(Entity* entity, size_t position);

    private:
        std::unordered_map<Entity*, size_t> m_mapEntIndex;
        std::vector<Entity*> m_vOrderedEntities;

        // 按 m_nId 排序的比较函数
        static bool compareById(Entity* a, Entity* b)
        {
            return a->getId() < b->getId();
        }
    };
}

#endif // ORDERMANAGER_H
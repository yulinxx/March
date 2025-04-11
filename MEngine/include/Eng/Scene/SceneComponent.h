#ifndef SCENECOMPONENT_H
#define SCENECOMPONENT_H

#include <vector>
#include <memory>
#include "Entity/Entity.h"
#include "MEngineAPI.h"

namespace MEngine
{

    class MENGINE_API SceneComponent
    {
    public:
        virtual ~SceneComponent() = default;

    public:
        // 添加
        virtual void addEntity(Entity* entity)
        {
            if (entity)
            {
                addEntity(std::shared_ptr<Entity>(entity, [](Entity*) {}));
            }
        }

        virtual void addEntity(const std::vector<std::shared_ptr<Entity>>& entities)
        {
            for (auto& ent : entities)
            {
                addEntity(ent);
            }
        }

        virtual void addEntity(std::shared_ptr<Entity> entity) = 0;


        //template<typename T>
        //virtual void addEntity(const T>& entities) = 0;

        // 删除
        virtual void removeEntity(Entity* entity)
        {
            if (entity)
            {
                removeEntity(std::shared_ptr<Entity>(entity, [](Entity*) {}));
            }
        }

        virtual void removeEntity(const std::vector<Entity*>& entities)
        {
            for (auto ent : entities)
            {
                removeEntity(ent);
            }
        }

        virtual void removeEntity(std::shared_ptr<Entity> entity) = 0;

        virtual void removeEntity(const std::vector<std::shared_ptr<Entity>>& entities)
        {
            for (auto& ent : entities)
            {
                removeEntity(ent);
            }
        }
    };

}

#endif // SCENECOMPONENT_H
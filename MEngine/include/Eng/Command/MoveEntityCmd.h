#ifndef MOVEENTITYCMD_H
#define MOVEENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Scene.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API MoveEntityCmd : public Command
    {
    public:
        MoveEntityCmd(Scene* scene, const std::vector<std::shared_ptr<Entity>>& entities, const Ut::Vec2d& delta);
        ~MoveEntityCmd() = default;

        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene;
        std::vector<std::shared_ptr<Entity>> m_entities;
        Ut::Vec2d m_delta;
    };
}
#endif // MOVEENTITYCMD_H
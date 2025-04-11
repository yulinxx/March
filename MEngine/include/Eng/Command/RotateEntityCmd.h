#ifndef ROTATEENTITYCMD_H
#define ROTATEENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Scene.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API RotateEntityCmd : public Command
    {
    public:
        RotateEntityCmd(Scene* scene, const std::vector<std::shared_ptr<Entity>>& entities, double angle);
        ~RotateEntityCmd() = default;

        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene;
        std::vector<std::shared_ptr<Entity>> m_entities;
        double m_angle;
    };
}
#endif // ROTATEENTITYCMD_H
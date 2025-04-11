#ifndef TRANSFORMCMD_H
#define TRANSFORMCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Scene.h"
#include "Entity/Entity.h"
#include "Ut/Matrix.h"

namespace MEngine
{
    class MENGINE_API TransformCmd : public Command
    {
    public:
        TransformCmd(Scene* scene,
            const std::vector<std::shared_ptr<Entity>>& entities,
            const Ut::Mat3& transform);
        ~TransformCmd() = default;

        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene{ nullptr };
        std::vector<std::shared_ptr<Entity>> m_entities;
        Ut::Mat3 m_transform;
        Ut::Mat3 m_inverseTransform; // 用于撤销操作
    };
}
#endif // TRANSFORMCMD_H
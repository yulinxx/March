#ifndef DELENTITYCMD_H
#define DELENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Scene.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API DelEntityCmd final : public Command
    {
    public:
        DelEntityCmd(Scene* scene, std::shared_ptr<Entity> entity);
        DelEntityCmd(Scene* scene, std::vector<std::shared_ptr<Entity>> entities);
        ~DelEntityCmd();

    public:
        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene{ nullptr };
        std::vector<std::shared_ptr<Entity>> m_vEntities;
    };
}

#endif // DELENTITYCMD_H
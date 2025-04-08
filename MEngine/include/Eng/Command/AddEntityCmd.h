#ifndef ADDENTITYCMD_H
#define ADDENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Scene.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API AddEntityCmd : public Command
    {
    public:
        AddEntityCmd(Scene* scene, Entity* entity);
        AddEntityCmd(Scene* scene, std::shared_ptr<Entity> entity);
        ~AddEntityCmd();

    public:
        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene{ nullptr };
        Entity* m_entity{ nullptr };
    };
}

#endif // ADDENTITYCMD_H
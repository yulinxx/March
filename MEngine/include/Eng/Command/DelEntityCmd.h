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
        DelEntityCmd(Scene* scene, Entity* entity);
        ~DelEntityCmd();

    public:
        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Scene* m_scene{ nullptr };
        Entity* m_entity{ nullptr };
    };
}

#endif // DELENTITYCMD_H
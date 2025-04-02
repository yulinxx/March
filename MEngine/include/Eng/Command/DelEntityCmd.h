#ifndef DELENTITYCMD_H
#define DELENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Group.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API DelEntityCmd final : public Command
    {
    public:
        DelEntityCmd(Group* group, Entity* entity);
        ~DelEntityCmd();

    public:
        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Group* m_group{ nullptr };
        Entity* m_entity{ nullptr };
    };
}

#endif // DELENTITYCMD_H
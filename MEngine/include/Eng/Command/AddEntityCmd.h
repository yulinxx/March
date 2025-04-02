#ifndef ADDENTITYCMD_H
#define ADDENTITYCMD_H

#include "Command.h"
#include "MEngineAPI.h"
#include "Scene/Group.h"
#include "Entity/Entity.h"

namespace MEngine
{
    class MENGINE_API AddEntityCmd : public Command
    {
    public:
        AddEntityCmd(Group* group, Entity* entity);
        ~AddEntityCmd();

    public:
        void execute() override;
        void undo() override;
        void redo() override;

    private:
        Group* m_group{ nullptr };
        Entity* m_entity{ nullptr };
    };
}

#endif // ADDENTITYCMD_H
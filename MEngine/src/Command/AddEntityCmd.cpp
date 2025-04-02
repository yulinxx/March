#include "Command/AddEntityCmd.h"

namespace MEngine
{
    AddEntityCmd::AddEntityCmd(Group* group, Entity* entity)
        : m_group(group ? group : throw std::invalid_argument("Group pointer cannot be null")),
        m_entity(entity ? entity : throw std::invalid_argument("Entity pointer cannot be null"))
    {
    }

    AddEntityCmd::~AddEntityCmd()
    {
        if (m_group && m_entity)
            m_group->removeEntity(m_entity);

        SAFE_DEL(m_entity);
    }

    void AddEntityCmd::execute()
    {
        m_group->addEntity(m_entity);
    }

    void AddEntityCmd::undo()
    {
        m_group->removeEntity(m_entity);
    }

    void AddEntityCmd::redo()
    {
        execute();
    }
}
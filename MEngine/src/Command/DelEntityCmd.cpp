#include "Command/DelEntityCmd.h"

namespace MEngine
{
    DelEntityCmd::DelEntityCmd(Scene* scene, Entity* entity)
        : m_scene(scene ? scene : throw std::invalid_argument("Group pointer cannot be null")),
        m_entity(entity ? entity : throw std::invalid_argument("Entity pointer cannot be null"))
    {
    }

    DelEntityCmd::~DelEntityCmd()
    {
        // m_group->removeEntity(m_entity);
        // SAFE_DEL(m_entity);
    }

    void DelEntityCmd::execute()
    {
        m_scene->removeEntity(m_entity);
    }

    void DelEntityCmd::undo()
    {
        m_scene->addEntity(m_entity);
    }

    void DelEntityCmd::redo()
    {
        execute();
    }
}
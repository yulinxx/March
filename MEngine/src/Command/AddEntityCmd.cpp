#include "Command/AddEntityCmd.h"

namespace MEngine
{
    AddEntityCmd::AddEntityCmd(Scene* scene, Entity* entity)
        : m_scene(scene ? scene : throw std::invalid_argument("Group pointer cannot be null")),
        m_entity(entity ? entity : throw std::invalid_argument("Entity pointer cannot be null"))
    {
    }

    AddEntityCmd::AddEntityCmd(Scene* scene, std::shared_ptr<Entity> entity)
        : m_scene(scene ? scene : throw std::invalid_argument("Group pointer cannot be null")),
        m_entity(entity ? entity.get() : throw std::invalid_argument("Entity pointer cannot be null"))
    {
    }

    AddEntityCmd::~AddEntityCmd()
    {
        // if (m_group && m_entity)
        //     m_group->removeEntity(m_entity);

        // SAFE_DEL(m_entity);
    }

    void AddEntityCmd::execute()
    {
        m_scene->addEntity(m_entity);
    }

    void AddEntityCmd::undo()
    {
        m_scene->removeEntity(m_entity);
    }

    void AddEntityCmd::redo()
    {
        execute();
    }
}
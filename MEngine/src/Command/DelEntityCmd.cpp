#include "Command/DelEntityCmd.h"

namespace MEngine
{
    DelEntityCmd::DelEntityCmd(Scene* scene, std::shared_ptr<Entity> entity)
        : m_scene(scene)
    {
        m_vEntities.push_back(entity);
    }

    DelEntityCmd::DelEntityCmd(Scene* scene, std::vector<std::shared_ptr<Entity>> entities)
        : m_scene(scene), m_vEntities(std::move(entities))
    {
    }

    DelEntityCmd::~DelEntityCmd()
    {
        for (auto& entity : m_vEntities)
            entity.reset();
    }

    void DelEntityCmd::execute()
    {
        for (auto& entity : m_vEntities)
        {
            m_scene->removeEntity(entity.get());
        }
    }

    void DelEntityCmd::undo()
    {
        for (auto& entity : m_vEntities)
        {
            m_scene->addEntity(entity.get());
        }
    }

    void DelEntityCmd::redo()
    {
        execute();
    }
}
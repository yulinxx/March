#include "Command/TransformCmd.h"

namespace MEngine
{
    TransformCmd::TransformCmd(Scene* scene,
        const std::vector<std::shared_ptr<Entity>>& entities,
        const Ut::Mat3& transform)
        : m_scene(scene), m_entities(entities), m_transform(transform)
    {
        m_inverseTransform = transform.inverse();
    }

    void TransformCmd::execute()
    {
        for (auto& entity : m_entities)
        {
            entity->transform(m_transform);
        }
    }

    void TransformCmd::undo()
    {
        for (auto& entity : m_entities)
        {
            entity->transform(m_inverseTransform);
        }
    }

    void TransformCmd::redo()
    {
        execute();
    }
}
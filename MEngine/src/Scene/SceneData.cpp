#include "Scene/SceneData.h"

#include "Logger.h"
#include "Scene/Group.h"
#include "Scene/Previews.h"

#include "Command/CommandManager.h"

namespace MEngine
{
    SceneData::SceneData()
    {
        init();
    }

    SceneData::~SceneData()
    {
        SAFE_DEL(m_rootGroup);
        SAFE_DEL(m_entTree);
        SAFE_DEL(m_cmdManager);
        SAFE_DEL(m_drawData);
        SAFE_DEL(m_previews);
    }

    void SceneData::init()
    {
        m_rootGroup = new Group();
        MLog::Logger::LogInfo("Scene created");

        m_cmdManager = new CommandManager(20);
        m_entTree = new EntityIndex();
        m_drawData = new DrawData();
        m_previews = new Previews();
        m_matOrtho.identity();
    }

    void SceneData::insert(std::shared_ptr<Entity> entity, const Ut::Rect2d& box)
    {
        //if (entity)
        //{
        //    m_entTree->insert(std::make_pair(box, entity));
        //}
    }

    void SceneData::insert(Entity* entity, const Ut::Rect2d& box)
    {
        //if (entity)
        //{
        //    m_entTree->insert(std::make_pair(box, std::shared_ptr<Entity>(entity, [](Entity*) {}))); // 不释放原始指针
        //}
    }

    void SceneData::addEntity(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities)
    {
        //for (const auto& [entity, box] : entities)
        //{
        //    if (entity)
        //    {
        //        m_entTree->insert(std::make_pair(box, entity));
        //    }
        //}
    }

    bool SceneData::remove(const std::shared_ptr<Entity>& entity, const Ut::Rect2d& box)
    {
        //if (entity)
        //{
        //    return m_entTree->remove(std::make_pair(box, entity)) > 0;
        //}
        return false;
    }

    bool SceneData::remove(Entity* entity, const Ut::Rect2d& box)
    {
        //if (entity)
        //{
        //    return m_entTree->remove(std::make_pair(box, std::shared_ptr<Entity>(entity, [](Entity*) {}))) > 0;
        //}
        return false;
    }

    size_t SceneData::removeEntity(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities)
    {
        //size_t count = 0;
        //for (const auto& [entity, box] : entities)
        //{
        //    if (entity)
        //    {
        //        count += m_entTree->remove(std::make_pair(box, entity));
        //    }
        //}
        return 0;
    }
}
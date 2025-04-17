#include "Scene/SceneData.h"

#include "Logger.h"
#include "Scene/Group.h"
#include "Scene/Previews.h"

#include "Command/CommandManager.h"
#include "Scene/Layer/LayerManager.h"

namespace MEngine
{
    SceneData::SceneData()
    {
        init();
    }

    SceneData::~SceneData()
    {
        m_rootGroup.reset ();
        m_entTree.reset();
        m_cmdManager.reset();
        m_drawData.reset();
        m_previews.reset();

        m_layerManager.reset();
    }

    void SceneData::init()
    {
        m_layerManager = std::make_shared<LayerManager>();
        m_rootGroup = std::make_shared<Group>();
        //m_rootGroup->setLayerManager(m_layerManager.get());
        
        m_entTree = std::make_shared<EntityIndex>();
        m_orderManager = std::make_shared<OrderManager>();


        m_vecComponents.push_back(m_layerManager);
        m_vecComponents.push_back(m_rootGroup);
        m_vecComponents.push_back(m_entTree);
        m_vecComponents.push_back(m_orderManager);

        m_cmdManager = std::make_shared<CommandManager>(20);

        m_drawData = std::make_shared<DrawData>();
        m_previews = std::make_shared<Previews>();

        m_matOrtho.identity();

        MLog::Logger::LogInfo("Scene created");
    }

}
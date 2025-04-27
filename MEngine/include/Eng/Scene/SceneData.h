#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "DrawData/DrawData.h"
#include "Scene/EntityIndex.h"

#include "Scene/OrderManager.h"
// #include "RI/IRenderInterface.h"
#include "Scene/SceneComponent.h"
#include "Scene/Layer/LayerManager.h"

#include "Ut/Matrix.h"
#include "MEngineAPI.h"

typedef std::function<void()> RefreshCallback;

namespace  MEngine
{
    class Group;
    class Previews;
    class CommandManager;

    class MENGINE_API SceneData final
    {
    public:
        SceneData();
        ~SceneData();

    public:

    private:
        void init();

    public:
        std::shared_ptr<Group> m_rootGroup{ nullptr };
        std::shared_ptr<EntityIndex> m_entTree{ nullptr };
        std::shared_ptr<LayerManager> m_layerManager{ nullptr }; // 图层管理器
        std::shared_ptr<CommandManager> m_cmdManager{ nullptr }; // 命令
        std::shared_ptr<OrderManager> m_orderManager{ nullptr }; // 顺序

        //IRender::IRenderInterface* m_iRender{ nullptr };
        std::shared_ptr<DrawData> m_drawData{ nullptr };
        std::shared_ptr<Previews> m_previews{ nullptr };

        float m_dZoomFactor{ 1.0f };
        Ut::Matrix3d m_matOrtho;
        Ut::Vec2i m_vViewSize{ 800, 600 };

        RefreshCallback m_refreshCallback;

        std::vector<std::shared_ptr<SceneComponent>> m_vecComponents;
        std::set<std::shared_ptr<Entity>> m_setSels;
    };
}

#endif // SCENEDATA_H
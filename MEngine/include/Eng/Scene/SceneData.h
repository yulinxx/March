#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "DrawData/DrawData.h"
#include "Scene/EntityIndex.h"

// #include "RI/IRenderInterface.h"

#include "Ut/Matrix.h"

#include "MEngineAPI.h"

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
        void init();

    public:

    public:
        void insert(std::shared_ptr<Entity> entity, const Ut::Rect2d& box);
        void insert(Entity* entity, const Ut::Rect2d& box);
        void addEntity(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);
        bool remove(const std::shared_ptr<Entity>& entity, const Ut::Rect2d& box);
        bool remove(Entity* entity, const Ut::Rect2d& box);
        size_t removeEntity(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);

    public:
        Group* m_rootGroup{ nullptr };
        EntityIndex* m_entTree{ nullptr };
        CommandManager* m_cmdManager{ nullptr };

        Previews* m_previews{ nullptr };

        //IRender::IRenderInterface* m_iRender{ nullptr };
        DrawData* m_drawData{ nullptr };

        float m_dZoomFactor{ 1.0f };
        Ut::Matrix3d m_matOrtho;
        Ut::Vec2i m_vViewSize{ 800, 600 };
    };
}

#endif // SCENEDATA_H
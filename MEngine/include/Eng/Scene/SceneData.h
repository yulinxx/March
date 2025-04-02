#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "DrawData/DrawData.h"
#include "Scene/EntityIndex.h"
#include "Scene/Group.h"
#include "Command/CommandManager.h"
// #include "RI/IRenderInterface.h"

#include "Ut/Matrix.h"

#include "MEngineAPI.h"

namespace  MEngine
{
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
        void insertBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);
        bool remove(const std::shared_ptr<Entity>& entity, const Ut::Rect2d& box);
        bool remove(Entity* entity, const Ut::Rect2d& box);
        size_t removeBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);

    public:
        Group* m_rootGroup{ nullptr };
        EntityIndex* m_entTree{ nullptr };
        CommandManager* m_cmdManager{ nullptr };
        //IRender::IRenderInterface* m_iRender{ nullptr };
        DrawData* m_drawData{ nullptr };

        float m_dZoomFactor{ 1.0f };
        Ut::Matrix3d m_matOrtho;
        Ut::Vec2i m_vViewSize{ 800, 600 };
        //Ut::Matrix4d m_matOrtho;
        // Ut::Matrix3d m_projectionMatrix; // 投影矩阵，用于将3D场景转换为2D屏幕坐标
        // Ut::Matrix3d m_viewMatrix; // 视图矩阵，用于将3D场景转换为2D屏幕坐标
        // Ut::Matrix3d m_modelMatrix; // 模型矩阵，用于将3D场景转换为2D屏幕坐标
    };
}

#endif // SCENEDATA_H
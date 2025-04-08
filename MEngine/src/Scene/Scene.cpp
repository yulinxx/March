#include "Scene/Scene.h"
#include "Logger.h"

#include "Scene/Previews.h"

namespace MEngine
{
    Scene::Scene()
    {
        m_sceneData = new SceneData();
    }

    Scene::~Scene()
    {
        SAFE_DEL(m_sceneData);

        MLog::Logger::LogInfo("Scene destroyed");
    }

    void Scene::addEntity(Entity* entity)
    {
        if (m_sceneData->m_rootGroup)
        {
            m_sceneData->m_rootGroup->addEntity(entity);
            m_sceneData->m_entTree->addEntity(entity);
        }
    }

    bool Scene::removeEntity(Entity* entity)
    {
        if (m_sceneData->m_rootGroup)
        {
            m_sceneData->m_rootGroup->removeEntity(entity);
            m_sceneData->m_entTree->removeEntity(entity);
        }
        return false;
    }

    // void Scene::setRenderInterface(IRender::IRenderInterface* i)
    // {
    //     //m_iRender = i;
    // }

    Group* Scene::getRootGroup()
    {
        return m_sceneData->m_rootGroup;
    }

    CommandManager* Scene::getCmdManager()
    {
        return m_sceneData->m_cmdManager;
    }

    void Scene::addPreview(Entity* entity)
    {
        m_sceneData->m_previews->addEntity(entity);
    }

    void Scene::removePreview(Entity* entity)
    {
        m_sceneData->m_previews->removeEntity(entity);
    }

    void Scene::paint()
    {
        getDrawData()->clear();
        m_sceneData->m_drawData->processEntities(m_sceneData->m_rootGroup);
        m_sceneData->m_drawData->processPreviews(m_sceneData->m_previews);
    }

    DrawData* Scene::getDrawData()
    {
        return m_sceneData->m_drawData;
    }

    Mat3& Scene::getViewMatrix() const
    {
        return m_sceneData->m_matOrtho;
    }

    void Scene::zoom(float scaleFactor)
    {
        if (m_sceneData)
        {
            m_sceneData->m_matOrtho.scale(scaleFactor);
        }
    }

    void Scene::move(const Ut::Vec2& delta)
    {
        if (m_sceneData)
        {
            m_sceneData->m_matOrtho.translation(delta);
        }
    }

    void Scene::reset()
    {
        if (m_sceneData)
        {
            m_sceneData->m_dZoomFactor = 1.0;
            m_sceneData->m_matOrtho.identity();
        }
    }

    Ut::Vec2d Scene::worldToScreen(const Ut::Vec2d& worldPos) const
    {
        // 1. 世界坐标 -> NDC (使用 3x3 正交矩阵)
        Ut::Vec3d homoWorld(worldPos.x(), worldPos.y(), 1.0); // 齐次坐标
        Ut::Vec3d homoNdc = m_sceneData->m_matOrtho * homoWorld;
        Ut::Vec2d ndc(homoNdc.x() / homoNdc.z(), homoNdc.y() / homoNdc.z()); // 归一化

        // 2. NDC [-1, 1] -> 屏幕坐标 [0, width] x [0, height]
        float screenX = (ndc.x() + 1.0) * m_sceneData->m_vViewSize.x() / 2.0;  // x: [-1, 1] -> [0, width]
        float screenY = (1.0 - ndc.y()) * m_sceneData->m_vViewSize.y() / 2.0;  // y: [-1, 1] -> [0, height]
        return Ut::Vec2d(screenX, screenY);
    }

    Ut::Vec2d Scene::screenToWorld(const Ut::Vec2d& screenPos) const
    {
        // 1. 屏幕坐标 [0, width] x [0, height] -> NDC [-1, 1]
        float ndcX = (2.0 * screenPos.x() / m_sceneData->m_vViewSize.x()) - 1.0;  // x: [0, width] -> [-1, 1]
        float ndcY = 1.0 - (2.0 * screenPos.y() / m_sceneData->m_vViewSize.y()); // y: [0, height] -> [-1, 1]

        // 2. NDC -> 世界坐标 (使用逆矩阵)
        Ut::Matrix3d invOrtho = m_sceneData->m_matOrtho.inverse(); // 计算逆矩阵
        Ut::Vec3d homoNdc(ndcX, ndcY, 1.0); // 齐次坐标
        Ut::Vec3d homoWorld = invOrtho * homoNdc;
        return Ut::Vec2d(homoWorld.x() / homoWorld.z(), homoWorld.y() / homoWorld.z()); // 归一化
    }

    Ut::Vec2d Scene::ndcToWorld(const Ut::Vec2d& ndcPos) const
    {
        // NDC -> 世界坐标 (使用逆矩阵)
        Ut::Matrix3d invOrtho = m_sceneData->m_matOrtho.inverse(); // 计算逆矩阵
        Ut::Vec3d homoNdc(ndcPos.x(), ndcPos.y(), 1.0); // 齐次坐标
        Ut::Vec3d homoWorld = invOrtho * homoNdc;
        return Ut::Vec2d(homoWorld.x() / homoWorld.z(), homoWorld.y() / homoWorld.z()); // 归一化
    }

    Ut::Vec2d Scene::worldToNdc(const Ut::Vec2d& worldPos) const
    {
        // 世界坐标 -> NDC (使用 3x3 正交矩阵)
        Ut::Vec3d homoWorld(worldPos.x(), worldPos.y(), 1.0); // 齐次坐标
        Ut::Vec3d homoNdc = m_sceneData->m_matOrtho * homoWorld;
        return Ut::Vec2d(homoNdc.x() / homoNdc.z(), homoNdc.y() / homoNdc.z()); // 归一化
    }

    void Scene::execute(CommandPtr cmd)
    {
        m_sceneData->m_cmdManager->execute(std::move(cmd));
    }

    void Scene::redo()
    {
        m_sceneData->m_cmdManager->redo();
    }

    void Scene::undo()
    {
        m_sceneData->m_cmdManager->undo();
    }

    void Scene::setView(size_t width, size_t height)
    {
        if (width != 0 && height != 0)
        {
            m_sceneData->m_vViewSize = Ut::Vec2i(width, height);

            m_sceneData->m_dZoomFactor = 1.0;
            m_sceneData->m_matOrtho.ortho2D(0.0, static_cast<double>(width),
                0.0, static_cast<double>(height));
        }
    }

    void Scene::setView(Ut::Rect2d& rect)
    {
        if (rect.area() > 0)
        {
            int w = rect.width();
            int h = rect.height();
            m_sceneData->m_vViewSize = Ut::Vec2i{ w, h };
        }
    }

    void Scene::setView(Ut::Vec2& ptCenter, Ut::Vec2i& ptSize)
    {
        double halfWidth = ptSize.x() / 2.0;
        double halfHeight = ptSize.y() / 2.0;
        double left = ptCenter.x() - halfWidth;
        double right = ptCenter.x() + halfWidth;
        double bottom = ptCenter.y() - halfHeight;
        double top = ptCenter.y() + halfHeight;

        m_sceneData->m_matOrtho.ortho2D(left, right, bottom, top);

        m_sceneData->m_vViewSize = ptSize;

        m_sceneData->m_dZoomFactor = 1.0;
    }

    Ut::Vec2d Scene::getViewSize()
    {
        double a = m_sceneData->m_matOrtho.at(0, 0);
        double b = m_sceneData->m_matOrtho.at(1, 1);
        double tx = m_sceneData->m_matOrtho.at(0, 2);
        double ty = m_sceneData->m_matOrtho.at(1, 2);

        // 计算宽度和高度
        double width = 2.0 / a;
        double height = 2.0 / b;

        // 计算中心点
        double centerX = -tx / a;
        double centerY = -ty / b;

        return Ut::Vec2d(width, height);
    }

    Ut::Vec2d Scene::getViewCenter()
    {
        double a = m_sceneData->m_matOrtho.at(0, 0);
        double b = m_sceneData->m_matOrtho.at(1, 1);
        double tx = m_sceneData->m_matOrtho.at(0, 2);
        double ty = m_sceneData->m_matOrtho.at(1, 2);

        // 计算宽度和高度
        double width = 2.0 / a;
        double height = 2.0 / b;

        // 计算中心点
        double centerX = -tx / a;
        double centerY = -ty / b;

        return Ut::Vec2d(centerX, centerY);
    }

    void Scene::setZoom(float dScale)
    {
        auto res = m_sceneData->m_dZoomFactor * dScale;
        if ((res < 0.1) || (res > 10.0))
        {
            return;
        }

        m_sceneData->m_dZoomFactor = res;
        m_sceneData->m_matOrtho.scale(dScale);
    }

    float Scene::getViewScale()
    {
        return m_sceneData->m_dZoomFactor;
    }

    void Scene::zoomAt(const Ut::Vec2& viewPos, double factor)
    {
        if (!m_sceneData)
            return;

        m_sceneData->m_matOrtho.scale(factor, factor, viewPos[0], viewPos[1]);
    }

    void Scene::pan(const Ut::Vec2& offset)
    {
        if (!m_sceneData)
            return;

        m_sceneData->m_matOrtho.translation(offset[0], offset[1]);
    }

    void Scene::resetView()
    {
        if (!m_sceneData)
            return;

        m_sceneData->m_matOrtho.identity();
    }
} // namespace MEngine
#ifndef SCENE_H
#define SCENE_H

#include "Scene/SceneData.h"

//#include "IRender/IRenderInterface.h"

namespace MEngine
{
    class MENGINE_API Scene
    {
    public:
        Scene();
        ~Scene();

    public:
        // void addEntity(Entity* entity, Group* parent = nullptr);
        // bool removeEntity(Entity* entity);

         //void setRenderInterface(IRender::IRenderInterface* i);

        Group* getRootGroup();
        CommandManager* getCmdManager();

        void paint();   // 绘图入口
        DrawData* getDrawData();

        Mat3& getViewMatrix() const; // 获取视口矩阵

        //void resize(size_t width, size_t height);
        void setView(size_t width, size_t height); // 设置视口大小
        void setView(Ut::Rect2d& rect); // 设置视口大小
        void setView(Ut::Vec2& ptCenter, Ut::Vec2i& ptSize); // 中点/大小
        Ut::Vec2d getViewSize();
        Ut::Vec2d getViewCenter();

        void setZoom(float dScale); // 设置缩放比例
        float getViewScale();

        void zoomAt(const Ut::Vec2& viewPos, double factor);
        void pan(const Ut::Vec2& offset);
        void resetView();

        // 添加缩放、移动、重置的方法
        void zoom(float scaleFactor);
        void move(const Ut::Vec2& delta);
        void reset();

        Ut::Vec2d worldToScreen(const Ut::Vec2d& worldPos) const;
        Ut::Vec2d screenToWorld(const Ut::Vec2d& screenPos) const;
        Ut::Vec2d ndcToWorld(const Ut::Vec2d& ndcPos) const;
        Ut::Vec2d worldToNdc(const Ut::Vec2d& worldPos) const;

        // 执行操作命令
        void execute(CommandPtr cmd);
        void redo();
        void undo();

    private:
        SceneData* m_sceneData{ nullptr };
    };
}

#endif // SCENE_H
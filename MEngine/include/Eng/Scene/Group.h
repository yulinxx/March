#ifndef GROUP_H
#define GROUP_H

#include "Scene/SceneComponent.h"

namespace MEngine
{
    class MENGINE_API Group : public SceneComponent
    {
    public:
        Group();
        ~Group();

    public:
        virtual void addEntity(std::shared_ptr<Entity> entity) override;
        virtual void removeEntity(std::shared_ptr<Entity> entity) override;

    public:
        size_t getChildrenCount() const;
        Entity* getChild(size_t index) const;

        template<typename Func>
        void forEachEntity(Func&& func) const;

    private:
        struct Impl;
        Impl* m_pImpl = nullptr;
    };
}

#endif // GROUP_H
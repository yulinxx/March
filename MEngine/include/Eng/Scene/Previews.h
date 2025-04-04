#ifndef PREVIEWS_H
#define PREVIEWS_H

#include "MEngineAPI.h"
#include <memory>

namespace MEngine
{
    class Entity;

    class MENGINE_API Previews
    {
    public:
    Previews();
        ~Previews();

    public:
        void addEntity(Entity* entity);
        bool removeEntity(Entity* entity);

        size_t getChildrenCount() const;
        Entity* getChild(size_t index) const;


        template<typename Func>
        void forEachEntity(Func&& func) const;

    private:
        struct Impl;
        Impl* m_pImpl = nullptr;
    };
}

#endif // PREVIEWS_H
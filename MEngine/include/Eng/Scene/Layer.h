#ifndef LAYER_H
#define LAYER_H

#include "Entity/Entity.h"
#include <vector>
#include <memory>

namespace MEigen
{
    class Layer
    {
    public:
        // explicit Layer(const std::string &name);

    //     void addEntity(std::shared_ptr<Entity> entity);
    //     void removeEntity(std::shared_ptr<Entity> entity);

    //     void setLocked(bool locked) { m_locked = locked; }
    //     void setVisible(bool visible) { m_visible = visible; }
    //     void setProcessing(bool processing) { m_processing = processing; }

    //     bool isLocked() const { return m_locked; }
    //     bool isVisible() const { return m_visible; }
    //     bool isProcessing() const { return m_processing; }

    //     const std::vector<std::shared_ptr<Entity>> &getEntities() const { return m_entities; }
    //     const std::string &getName() const { return m_name; }

    // private:
    //     std::string m_strName;
    //     bool m_locked = false;
    //     bool m_visible = true;
    //     bool m_processing = false;
    //     std::vector<std::shared_ptr<Entity>> m_entities;
    };
}
#endif // LAYER_H
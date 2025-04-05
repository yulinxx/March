#include "Entity/Entity.h"
#include <string>

// #define _SILENCE_ALL_CXX23_DEPRECATION_WARNINGS
// #include <Eigen/src/Core/arch/Default/BFloat16.h>

namespace MEngine
{
    Entity::Entity()
    {
    }

    Entity::~Entity()
    {
    }

    // const std::string &Entity::getName() const
    // {
    //     return m_strName;
    // }

    // void Entity::setName(const std::string &name)
    // {
    //     m_strName = name;
    // }

    Ut::Vec2d Entity::getValue(double t)
    {
        return m_basePt;
    }

    double Entity::EvalParam(const Ut::Vec2& p)
    {
        return 0;
    }
}
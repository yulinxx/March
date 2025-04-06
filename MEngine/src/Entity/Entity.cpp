#include "Entity/Entity.h"
#include <string>

namespace MEngine
{
    struct Entity::Impl
    {
        EntType type = EntType::UNKNOWN;  // ʵ������
        size_t id = 0;                    // ʵ�� ID
        Ut::Vec2d basePt;                 // ��׼��
        bool reverse = false;             // �Ƿ���
        bool closed = false;              // �Ƿ�պ�
        Ut::Rect2d rect;
    };

    Entity::Entity()
    {
        m_impl = new Impl();
    }

    Entity::~Entity()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    Ut::Vec2d Entity::getValue(double t)
    {
        return m_impl->basePt;  // Ĭ�Ϸ��ػ�׼��
    }

    double Entity::EvalParam(const Ut::Vec2& p)
    {
        return 0;  // Ĭ�Ϸ��� 0
    }

    Ut::Rect2d& Entity::getRect() const
    {
        return m_impl->rect;
    }

    // ��ȡ����
    EntType Entity::getType() const
    {
        return m_impl->type;
    }

    size_t Entity::getId() const
    {
        return m_impl->id;
    }

    Ut::Vec2d& Entity::getBasePoint() const
    {
        return m_impl->basePt;
    }

    bool Entity::isReversed() const
    {
        return m_impl->reverse;
    }

    bool Entity::isClosed() const
    {
        return m_impl->closed;
    }

    // ��������
    void Entity::setType(EntType type)
    {
        m_impl->type = type;
    }

    void Entity::setId(size_t id)
    {
        m_impl->id = id;
    }

    void Entity::setBasePoint(const Ut::Vec2d& basePt)
    {
        m_impl->basePt = basePt;
    }

    void Entity::setReversed(bool reverse)
    {
        m_impl->reverse = reverse;
    }

    void Entity::setClosed(bool closed)
    {
        m_impl->closed = closed;
    }
}
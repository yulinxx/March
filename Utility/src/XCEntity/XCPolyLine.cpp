#include "XCEntity/XCPolyLine.h"

namespace XC
{
    XCPolyLine::XCPolyLine(const XCPolyLine& other)
        : XCEntity(other)
    {
        // 深拷贝 m_vEntities
        m_vEntities.reserve(other.m_vEntities.size());
        for (const auto& entity : other.m_vEntities)
        {
            if (entity)
            {
                m_vEntities.push_back(cloneEntity(entity.get()));
            }
        }
    }

    XCPolyLine& XCPolyLine::operator=(const XCPolyLine& other)
    {
        if (this != &other)
        {
            // 先清理现有数据
            m_vEntities.clear();
            // 深拷贝实体
            m_vEntities.reserve(other.m_vEntities.size());
            for (const auto& entity : other.m_vEntities)
            {
                if (entity)
                {
                    m_vEntities.push_back(cloneEntity(entity.get()));
                }
            }

            // 拷贝基类成员
            eType = other.eType;
            id = other.id;
            ChannelPort = other.ChannelPort;
            basePoint = other.basePoint;
            reverse = other.reverse;
            isClosed = other.isClosed;
            m_LayerName = other.m_LayerName;
        }
        return *this;
    }

    void XCPolyLine::addEntity(XCEntity* entity)
    {
        if (entity != nullptr)
        {
            m_vEntities.push_back(std::unique_ptr<XCEntity>(entity));
        }
    }

    size_t XCPolyLine::getEntityCount() const
    {
        return m_vEntities.size();
    }

    XCEntity* XCPolyLine::getEntity(size_t index) const
    {
        if (index < m_vEntities.size())
        {
            return m_vEntities[index].get();
        }
        return nullptr;
    }

    Ut::Vec2d XCPolyLine::value(double t)
    {
        if (m_vEntities.empty())
        {
            return basePoint; // 如果没有实体，返回基点
        }

        double segmentLength = 1.0 / m_vEntities.size();
        size_t segmentIndex = static_cast<size_t>(t / segmentLength);
        if (segmentIndex >= m_vEntities.size())
        {
            segmentIndex = m_vEntities.size() - 1;
        }

        double localT = (t - segmentIndex * segmentLength) / segmentLength;
        return m_vEntities[segmentIndex]->value(localT);
    }

    double XCPolyLine::EvalParam(const Ut::Vec2d& p)
    {
        if (m_vEntities.empty())
        {
            return 0.0; // 如果没有实体，返回默认值
        }

        // 遍历所有实体，找到最近的点并计算参数 t
        double minDist = std::numeric_limits<double>::max();
        double resultT = 0.0;
        double segmentLength = 1.0 / m_vEntities.size();

        for (size_t i = 0; i < m_vEntities.size(); ++i)
        {
            double tLocal = m_vEntities[i]->EvalParam(p);
            Ut::Vec2d point = m_vEntities[i]->value(tLocal);
            double dist = (point - p).length();
            if (dist < minDist)
            {
                minDist = dist;
                resultT = segmentLength * i + tLocal * segmentLength;
            }
        }
        return resultT;
    }

    std::unique_ptr<XCEntity> XCPolyLine::cloneEntity(const XCEntity* entity) const
    {
        if (!entity)
            return nullptr;

        // 临时实现：简单创建一个新对象并复制基本属性
        std::unique_ptr<XCEntity> newEntity = std::make_unique<XCEntity>();
        newEntity->eType = entity->eType;
        newEntity->id = entity->id;
        newEntity->ChannelPort = entity->ChannelPort;
        newEntity->basePoint = entity->basePoint;
        newEntity->reverse = entity->reverse;
        newEntity->isClosed = entity->isClosed;
        newEntity->m_LayerName = entity->m_LayerName; // 注意：浅拷贝
        return newEntity;
    }
}
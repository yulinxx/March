#include "Entity/Polygon.h"
#include <vector>

namespace MEngine
{
    struct Polygon::Impl
    {
        std::vector<Ut::Vec2> vVertices;
    };

    Polygon::Polygon()
    {
        m_impl = new Impl();
        m_eType = EntType::POLYGON;
    }

    Polygon::~Polygon()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Polygon::clear()
    {
        m_impl->vVertices.clear();
        m_impl->vVertices.shrink_to_fit();
    }

    void Polygon::addVertex(const Ut::Vec2& vertex)
    {
        m_impl->vVertices.push_back(vertex);
    }

    void Polygon::closePolygon()
    {
        if (m_impl->vVertices.size() > 2)
        {
            m_impl->vVertices.push_back(m_impl->vVertices.front());
        }
    }

    std::pair<Ut::Vec2*, size_t> Polygon::getLinesData() const
    {
        return {m_impl->vVertices.data(),
            m_impl->vVertices.size() };
    }

}
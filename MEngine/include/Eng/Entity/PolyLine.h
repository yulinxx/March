#ifndef POLYLINE_H
#define POLYLINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API PolyLine : public Entity
    {
    public:
        PolyLine();
        PolyLine(const std::vector<Ut::Vec2>& points, bool closed = false);
        ~PolyLine() override;

    public:
        void clear();

        // �������ж���
        void setPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // ��ӵ�������
        void addPoint(const Ut::Vec2& point);
        // �����Ƿ�պ�
        void setClosed(bool closed);

        // ��ȡ�������ݣ����ڻ���
        std::pair<Ut::Vec2*, size_t> getData() const;

        // ��ȡ���ж���
        std::vector<Ut::Vec2> getPoints() const;

        // ��ȡ�ܳ���
        double getLength() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // POLYLINE_H
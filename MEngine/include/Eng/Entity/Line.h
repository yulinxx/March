#ifndef LINE_H
#define LINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Line : public Entity
    {
    public:
        Line();
        Line(const Ut::Vec2& start, const Ut::Vec2& end);
        ~Line() override;

    public:
        void clear();

        // �����߶ε������˵�
        void setPoints(const Ut::Vec2& start, const Ut::Vec2& end);

        // �����յ�
        void setEndPoint(const Ut::Vec2& end);

        // ��ȡ�������ݣ����ڻ���
        std::pair<Ut::Vec2*, size_t> getData() const;

        // ��ȡ�˵�
        void getPoints(Ut::Vec2& start, Ut::Vec2& end) const;
        void getEndPoint(Ut::Vec2& end) const;

        // ��ȡ����
        double getLength() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // LINE_H
#ifndef IMAGE_H
#define IMAGE_H

#include "Entity/Entity.h"
#include <vector>
#include <memory>

namespace MEngine
{
    class Image : public Entity
    {
    public:
        Image();
        explicit Image(const char* filePath);
        ~Image();
        
    public:
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        void loadFromFile(const char* filePath);
        void setSize(const Ut::Vec2& size);
        Ut::Vec2 getSize() const;
        
        // 获取位图数据接口
        unsigned char* getPixelData() const;
        int getWidth() const;
        int getHeight() const;
        int getChannels() const;
        
        
    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // IMAGE_H
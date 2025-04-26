#ifndef IMAGE_H
#define IMAGE_H

#include "Entity/Entity.h"
#include <vector>
#include <memory>

namespace MEngine
{
    class MENGINE_API Image : public Entity
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
        void loadFromFile(const char* filePath); // 加载位图
        void setPosition(const Ut::Vec2& pos);   // 设置显示位置
        void setSize(const Ut::Vec2& size);      // 设置显示大小
        Ut::Vec2 getSize() const;                // 获取显示大小

        // 获取位图数据接口
        unsigned char* getImageData() const;
        int getWidth() const;
        int getHeight() const;
        int getChannels() const;

        // 获取纹理坐标（供 ImageDatas 使用）
        const std::vector<Ut::Vec2>& getTexCoords() const;

        // 获取变换矩阵（供 ImageDatas 存储到 SSBO）
        const Ut::Mat3& getTransform() const;

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // IMAGE_H
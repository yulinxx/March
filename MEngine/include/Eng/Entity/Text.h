#ifndef TEXT_H
#define TEXT_H

#include "Entity.h"
#include <string>

namespace MEngine
{
    class MENGINE_API Text : public Entity
    {
    public:
        Text();
        ~Text() override;

    public:
        // double BaseHeight;
        // std::string FontName;
        // double Height;
        // std::string text;
    };
}

#endif  // TEXT_H
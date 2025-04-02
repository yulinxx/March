#ifndef TEXT_H
#define TEXT_H

#include "Entity.h"
#include <string>

namespace MEngine
{
    class MENGINE_API Text : public Entity
    {
    public:
        // double BaseHeight;
        // std::string FontName;
        // double Height;
        // std::string text;

        Text();
        ~Text() override;
    };
}

#endif  // TEXT_H
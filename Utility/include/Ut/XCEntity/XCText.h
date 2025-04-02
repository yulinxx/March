#ifndef XCTEXT_H
#define XCTEXT_H

#include "XCEntity.h"
#include "../UtilityAPI.h"

#include <string>

namespace XC
{
    struct UTILITY_API XCText : public XCEntity
    {
        /**
         * @brief 文本的基准高度，通常用于定位文本的基线位置。
         *
         * 该值表示文本在垂直方向上的基准高度，可能用于确定文本的起始位置或与其他元素的对齐方式。
         */
        double dBaseHeight;
        /**
         * @brief 字体名称的字符指针。
         *
         * 指向一个以空字符结尾的字符串，该字符串表示文本所使用的字体名称。
         * 注意：使用完后需要手动管理内存，避免内存泄漏。
         */
        char* chFontName;
        /**
         * @brief 文本的实际高度。
         *
         * 该值表示文本在垂直方向上的实际显示高度。
         */
        double dHeight;
        /**
         * @brief 文本内容的字符指针。
         *
         * 指向一个以空字符结尾的字符串，该字符串包含了要显示的文本内容。
         * 注意：使用完后需要手动管理内存，避免内存泄漏。
         */
        char* chText;
    };
}

#endif // XCTEXT_H
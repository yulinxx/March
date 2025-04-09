#include "Shader/ShaderDef.h"

const char* rulerFS = R"(
    #version 460
    out vec4 fragColor;
    void main()
    {
        fragColor = vec4(0.0, 0.0, 1.0, 1.0); // 蓝色标尺
    }
)";
#include "Shader/ShaderDef.h"

const char* crossFS = R"(
    #version 460
    in vec3 fragColor;
    out vec4 outColor;

    void main()
    {
        outColor = vec4(fragColor, 1.0);
    }
)";
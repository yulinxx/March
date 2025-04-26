#include "Shader/ShaderDef.h"

const char* imgFS = R"(
    #version 460
    //out vec4 fragColor;
    //void main()
    //{
    //    fragColor = vec4(0.0, 0.0, 1.0, 1.0); // 蓝色标尺
    //}

    out vec4 FragColor;
    in vec2 TexCoord;

    uniform sampler2D texture1;

    void main() {
        FragColor = texture(texture1, TexCoord);
    }
)";
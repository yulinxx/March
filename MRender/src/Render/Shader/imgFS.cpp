#include "Shader/ShaderDef.h"

const char* imgFS = R"(
    #version 460

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D imageTexture;

    void main() {
        FragColor = texture(imageTexture, TexCoord);
    }
)";
#include "Shader/ShaderDef.h"

const char* imgVS = R"(
    #version 460
    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 aTexCoord;

    uniform mat4 projection;
    uniform vec2 translation;
    uniform float scale = 1.0;

    out vec2 TexCoord;

    void main()
    {
        vec3 scaledPos = vec3(position + translation, 0.0);
        gl_Position = projection * vec4(scaledPos, 1.0);

        TexCoord = aTexCoord;
    }

)";
#include "Shader/ShaderDef.h"

const char* linesVS = R"(
            #version 460
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec3 color;
            uniform mat4 projection;
            uniform vec2 translation;
            uniform float scale = 1.0;
            out vec3 fragColor;
            void main()
            {
                vec3 scaledPos = vec3(position.xy * scale + translation, position.z);
                gl_Position = projection * vec4(scaledPos, 1.0);
                fragColor = color;
            }
        )";
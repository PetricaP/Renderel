#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_LightPos;

in vec4 o_Pos;

void main() {
        float intensity = 1.0f / length(o_Pos.xy - u_LightPos) * 30.0f;
        color = u_Color * intensity;
}

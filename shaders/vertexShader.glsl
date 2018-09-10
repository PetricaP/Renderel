#version 330 core

layout(location = 0) in vec2 i_Position;
layout(location = 1) in vec2 i_TexCoord;

uniform mat4 u_Proj;
uniform mat4 u_Model;

out vec4 v_Pos;
out vec2 v_TexCoord;

void main() {
        vec4 position4 = vec4(i_Position, 0.0f, 1.0f);
        gl_Position = u_Proj * u_Model * position4;
        v_Pos = u_Model * position4;
        v_TexCoord = i_TexCoord;
}

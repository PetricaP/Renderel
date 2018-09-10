#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_Proj;
uniform mat4 u_Model;

out vec4 o_Pos;

void main() {
        gl_Position = u_Proj * u_Model * position;
        o_Pos = u_Model * position;
}

#version 330 core

layout(location = 0) in vec2 position;
out vec2 pos;

uniform mat4 u_Proj;

void main() {
	gl_Position = u_Proj * vec4(position, 0.0f, 1.0f);
	pos = position;
}

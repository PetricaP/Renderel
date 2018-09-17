#version 330 core

in vec3 position;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);

void main() {
	gl_Position = u_Proj * u_Model * vec4(position, 1.0f);
}

#version 330 core

layout(location = 0) in vec3 i_Position;

out vec3 v_TexCoord;

uniform mat4 u_Proj;
uniform mat4 u_View;

void main() {
	v_TexCoord = i_Position;
	vec4 pos = u_Proj * u_View * vec4(i_Position, 1.0);
	gl_Position = pos.xyww;
}

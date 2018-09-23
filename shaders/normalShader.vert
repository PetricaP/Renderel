#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TexCoord;
layout(location = 2) in vec3 i_Normal;
layout(location = 3) in vec3 i_Tangent;
layout(location = 4) in vec3 i_Bitangent;

uniform mat4 u_Proj;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec3 v_Pos;
out vec2 v_TexCoord;
out vec3 v_Normal;

void main() {
	vec4 position4 = vec4(i_Position, 1.0f);
	v_Pos = vec3(u_Model * position4);
	gl_Position = u_Proj * u_View * u_Model * position4;
	v_TexCoord = i_TexCoord;
//	v_Normal = mat3(transpose(inverse(u_Model))) * i_Normal;
	v_Normal = vec3(u_Model * vec4(i_Normal, 0.0));
//	v_Normal = vec3(u_View * u_Model * vec4(i_Normal, 0.0));
}

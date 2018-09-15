#version 330 core

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TexCoord;

uniform mat4 u_Proj = mat4(1.0f);
uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_View = mat4(1.0f);

out vec4 v_Pos;
out vec2 v_TexCoord;

void main() {
	vec4 position4 = vec4(i_Position, 1.0f);
	gl_Position = u_View * u_Proj * u_Model * position4;
	v_Pos = u_Model * position4;
	v_TexCoord = i_TexCoord;
}

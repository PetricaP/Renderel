#version 330 core

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 i_Position;
layout(location = 1) in float i_index;

uniform mat4 u_ColorMatrix = mat4(1.0f);

out vec4 v_Color;

void main() {
	v_Color = transpose(u_ColorMatrix)[int(i_index)];
	gl_Position = vec4(i_Position, 1.0f);
}

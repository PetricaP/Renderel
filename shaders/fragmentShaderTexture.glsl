#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_LightPos;
uniform sampler2D u_Sampler;

in vec4 v_Pos;
in vec2 v_TexCoord;

void main() {
	vec4 texColor = texture2D(u_Sampler, v_TexCoord);
	color = texColor;
}

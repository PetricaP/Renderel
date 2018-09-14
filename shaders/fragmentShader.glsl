#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_LightPos;
uniform sampler2D u_Sampler;

in vec4 v_Pos;
in vec2 v_TexCoord;

void main() {
	vec4 texColor = texture(u_Sampler, v_TexCoord);
	float intensity = 1.0f / length(v_Pos.xy - u_LightPos) * 0.20f;
	color = u_Color * intensity * 0.45 + texColor * 0.45 +
	vec4(0.1f, 0.1f, 0.1f, 0.0f);
}

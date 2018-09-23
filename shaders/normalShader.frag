#version 330 core

layout(location = 0) out vec4 color;

#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec3 v_Pos;
layout(location = 1) in vec2 v_TexCoord;
layout(location = 2) in vec3 v_Normal;


uniform vec3 u_CameraPosition;
// u_Texture is a normal map
uniform sampler2D u_Texture;
uniform samplerCube u_Cubemap;


void main() {

	/*vec3 normalRgb = vec3(texture(u_Texture, v_TexCoord));
	vec3 normal = normalize(normalRgb * 2.0 - 1.0);

	// Lower strength
	normal.y += 1.5;
	normal = normalize(normal);*/

//	vec3 normal = vec3(0.0, 1.0, 0.0);
	vec3 normal = v_Normal;
	vec3 incident = normalize(v_Pos - u_CameraPosition);
	vec3 reflected = reflect(incident, normal);
	vec3 texColor = texture(u_Cubemap, reflected).rgb;
	color = vec4(texColor, 1.0);
//	vec4 texColor = texture(u_Texture, v_TexCoord);
//	color = texColor;
}

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

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

void main() {

	vec3 normalRgb = vec3(texture(u_Texture, v_TexCoord));
	vec3 normalFromMap = normalize(normalRgb * 2.0 - 1.0);

	// Lower strength
	//normalFromMap.y += 1.5;
	//normalFromMap = normalize(normalFromMap);

//	vec3 normal = vec3(0.0, 1.0, 0.0);
	vec3 normal = v_Normal;
	vec3 incident = normalize(v_Pos - u_CameraPosition);

	mat3 TBN = cotangent_frame(normalize(normal), incident, v_TexCoord);
	vec3 finalNormal = normalize(TBN * normalFromMap);

	vec3 reflected = reflect(incident, normal);
	vec3 texColor = texture(u_Cubemap, reflected).rgb;

	color = vec4(texColor, 1.0);
//	vec4 texColor = texture(u_Texture, v_TexCoord);
//	color = texColor;
}

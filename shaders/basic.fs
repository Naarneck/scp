#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
uniform int mode;
uniform float loop;

void main()
{
	if (mode == 0)
		gl_FragColor = vec4(abs(sin(loop)),1.0,sin(loop),0.0) * clamp(dot(-vec3(0.0, 0.0, 1.0), normal0), 0.0, 1.0);
	else
	{
		gl_FragColor = texture2D(diffuse, texCoord0) 
		* clamp(dot(-vec3(0.0, 0.0, 1.0), normal0), 0.0, 1.0);
	}
}
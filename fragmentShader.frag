precision mediump float;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform vec3 spriteColor;

void main()
{
	gl_FragColor = vec4(spriteColor, 1.0) * texture2D(sampler2d, fTexCoord);
}
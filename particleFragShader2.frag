precision mediump float;
varying vec2 fTexCoord;
varying vec4 particleColor;

uniform sampler2D sampler2d;

void main()
{
	gl_FragColor = texture2D(sampler2d, fTexCoord) * particleColor;
}
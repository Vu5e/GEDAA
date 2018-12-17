attribute vec4 vVertex;

varying vec2 fTexCoord;
varying vec4 particleColor;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform vec2 offset;
uniform vec4 color;
uniform float scale;

void main()
{
	fTexCoord = vVertex.zw;
	particleColor = color;
	gl_Position = projectionMatrix * modelMatrix * vec4((vVertex.xy * scale) + offset, 0.0, 1.0);
}

attribute vec4 vVertex;

varying vec2 fTexCoord;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
	fTexCoord = vVertex.zw;
	gl_Position = projectionMatrix * modelMatrix * vec4(vVertex.xy, 0.0, 1.0);
}

precision mediump float;
varying vec2 fTexCoord;
varying vec4 particleColor;

uniform float Factor1;

uniform sampler2D sampler2d;

vec4 color_field_x()
{
	float midPoint = 640.0 / 3.0;
	float distance = 640.0 / 4.0;
	float r = 1.6 - min(gl_FragCoord.x / distance, 1.0);
	float g = 0.8 - min(2.0 * abs(gl_FragCoord.x - midPoint) / distance, 1.0);
	float b = 0.4 + max(gl_FragCoord.x - 2.0 * distance, 0.0) / distance;
	
	return vec4(r, g, b, 1.0);
}

vec4 color_field_y()
{
	float midPoint = 480.0 / 3.0;
	float distance = 480.0 / 4.0;
	float r = 1.6 - min(2.0 * abs(gl_FragCoord.y - midPoint) / distance, 1.0);
	float g = 0.4 + max(gl_FragCoord.y - 2.0 * distance, 0.0) / distance;
	float b = 0.8 - min(gl_FragCoord.y / distance, 1.0);
	
	return vec4(r, g, b, 1.0);
}

void main()
{
	gl_FragColor = texture2D(sampler2d, fTexCoord) * color_field_x() * color_field_y() * particleColor;
}
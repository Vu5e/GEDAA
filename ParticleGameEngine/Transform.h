#pragma once

#include "Vector.h"
#include <GLFW\glfw3.h>

class Transform
{
public:
	Vector2 Position, Scale;
	GLfloat Rotation;

	Transform(Vector2 position = Vector2(0.0f, 0.0f), Vector2 scale = Vector2(1.0f, 1.0f), GLfloat rotation = 0.0f)
	{
		Position = position;
		Scale = scale;
		Rotation = rotation;
	}

	void Translate(Vector2 direction)
	{
		Position.x += direction.x;
		Position.y += direction.y;
	}

	void Rotate(GLfloat angle)
	{
		Rotation += angle;
	}

private:

};
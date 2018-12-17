#pragma once

#include <GLFW\glfw3.h>
#include "Vector.h"

struct ParticleObject
{
	Vector2 Position;
	Vector2 Velocity;
	Vector4 Color;

	GLfloat Life, InitialLifeTime, Scale, InitialScale, Rotation, AngularSpeed, Mass;

	ParticleObject() : Scale(6.0f), InitialScale(2.0f), Life(0.0f), InitialLifeTime(1.0f), Rotation(2.0f), Mass(2.0f) {}
};
#pragma once

#include "GameObject.h"
#include "Vector.h"

class ParticleSpawn : public GameObject
{
public:
	GLfloat Radius;

	ParticleSpawn();
	ParticleSpawn(Vector2 pos, GLfloat radius, Vector2 velocity, Texture2D sprite);
	~ParticleSpawn();

	void Move(Vector2 direction)
	{
		direction = Vector2::normalize(direction);
		Vector2 displacement = Vector2(direction.x * Velocity.x, direction.y * Velocity.y);

		transform.Translate(displacement);
	}
};
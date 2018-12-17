#include "ParticleSpawn.h"

ParticleSpawn::ParticleSpawn()
	: GameObject(), Radius(12.5f) { }

ParticleSpawn::ParticleSpawn(Vector2 pos, GLfloat radius, Vector2 velocity, Texture2D sprite)
	: GameObject(pos, Vector2(radius * 2, radius * 2), sprite, Vector3(1.0f, 1.0f, 1.0f), velocity), Radius(radius) { }
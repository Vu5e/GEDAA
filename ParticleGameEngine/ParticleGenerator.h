#pragma once

#include <vector>
#include "Shader.h"
#include "texture2D.h"
#include "GameObject.h"
#include "ParticleAffector.h"

class ParticleGenerator
{
public:
	GameObject * Target;
	GLuint MaxAmount;
	Vector2 Offset, MaxSpeed, MinSpeed;
	GLfloat ParticleSize, ParticleMass, RespawnDelay, InitialLifeTime, MaxAngularSpeed;

	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount, GameObject * Target);

	void Configure(Vector2 MaxSpeed, Vector2 MinSpeed, GLfloat ParticleSize, GLfloat RespawnDelay, GLfloat InitialLifeTime, GLfloat MaxAngularSpeed);
	void AddAffectors(std::vector<ParticleAffector*> affectors);

	void Update(GLfloat dt);
	void Draw();

private:
	std::vector<ParticleObject> Particles;
	std::vector<ParticleAffector*> Affectors;

	Shader shader;
	Texture2D texture;
	GLfloat timer;

	void Init();
	GLuint FindUnusedParticle();
	void RespawnParticle();
};
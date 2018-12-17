#pragma once

#include "Vector.h"
#include "ParticleObject.h"
#include "GLFW/glfw3.h"

// ParticleAffector.h, this is an interface class for other affectors, no implementation.
// the pointer of each ParticleObject is received from particleSystem's update function. 
class ParticleAffector
{
public:
	virtual void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime) = 0;
};

// Color Affector
class ColorAffector : public ParticleAffector
{
public:
	virtual void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		if (particle->Color.w <= 0.0f)
		{
			particle->Life = 0.0f;
		}
	}
};

// Fading based on the Color
class FadeAffector : public ColorAffector
{
private:
	GLfloat FadeConstant;

public:
	FadeAffector(GLfloat FadeConstant) : FadeConstant(FadeConstant) {}

	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime) override
	{
		particle->Color.w -= FadeConstant * deltaTime;
		ColorAffector::AffectParticleUpdate(particle, deltaTime);
	}
};

// Scale Affector
class ScaleAffector : public ParticleAffector
{
private:
	GLfloat ScaleFactor;

public:
	ScaleAffector(GLfloat ScaleFactor) : ScaleFactor(ScaleFactor) {}

	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		particle->Scale *= ScaleFactor;
	}
};

// Scaling down the particle effects
class ScaleDownAffector : public ParticleAffector
{
public:
	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		if (particle->InitialLifeTime <= 0.0f)
		{
			return;
		}

		particle->Scale = particle->InitialScale * (particle->Life / particle->InitialLifeTime);
	}
};

// Position Affector
class PositionAffector : public ParticleAffector
{
public:
	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		Vector2 Displacement = particle->Velocity * deltaTime;
		particle->Position = particle->Position + Displacement;
	}
};

// Force Affector
class GravityAffector : public ParticleAffector
{
public:
	Vector2 Force;

	GravityAffector(Vector2 Force) : Force(Force) {}

	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		particle->Velocity = particle->Velocity + (Force * (10.0f / particle->Mass)) * deltaTime;
	}
};

// Rotation Affector
class RotationAffector : public ParticleAffector
{
public:
	void AffectParticleUpdate(ParticleObject* particle, GLfloat deltaTime)
	{
		particle->Rotation += particle->AngularSpeed * deltaTime;

		if (particle->Rotation >= 360.0f)
		{
			particle->Rotation -= 90.0f;
		}
	}
};


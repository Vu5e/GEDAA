#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, GLuint amount, GameObject * Target)
	: shader(shader), texture(texture), MaxAmount(amount), Target(Target)
{
	MaxSpeed = Vector2(150.0f, 150.0f);
	MinSpeed = MaxSpeed;
	MaxAngularSpeed = 0.0f;
	ParticleSize = 1.0f;
	ParticleMass = 1.0f;
	InitialLifeTime = 1.0f;
	Offset = Vector2(0.0f, 0.0f);
	RespawnDelay = 0.0f;
	timer = 0.0f;

	Init();
}

void ParticleGenerator::Configure(Vector2 MaxSpeed, Vector2 MinSpeed, GLfloat ParticleSize, 
	GLfloat RespawnDelay, GLfloat InitialLifeTime, GLfloat MaxAngularSpeed)
{
	this->MaxSpeed = MaxSpeed;
	this->MinSpeed = MinSpeed;
	this->ParticleSize = ParticleSize;
	this->RespawnDelay = RespawnDelay;
	this->InitialLifeTime = InitialLifeTime;
	this->MaxAngularSpeed = MaxAngularSpeed;
}

void ParticleGenerator::Update(GLfloat deltaTime)
{
	timer += deltaTime;

	if (timer >= RespawnDelay)
	{
		timer -= RespawnDelay;

		// Add new particles
		RespawnParticle();
	}

	// Update all available particles
	for (GLuint i = 0; i < Particles.size(); i++)
	{
		ParticleObject *p = &(Particles[i]);

		if (p->Life > 0.0f)
		{
			p->Life -= deltaTime;

			for (GLuint j = 0; j < Affectors.size(); j++)
			{
				Affectors[j]->AffectParticleUpdate(p, deltaTime);
			}
		}
	}
}

void ParticleGenerator::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.Use();

	for (ParticleObject particle : Particles)
	{
		if (particle.Life > 0.0f)
		{
			Matrix4 modelMatrix;

			modelMatrix = Matrix4::translate(Vector3(particle.Position.x, particle.Position.y, 0.0f)) *
				Matrix4::rotate(particle.Rotation, Vector3(0.0f, 0.0f, 1.0f)) *
				Matrix4::translate(Vector3(-particle.Position.x, -particle.Position.y, 0.0f));

			shader.SetVector2f("offset", particle.Position);
			shader.SetVector4f("color", particle.Color);
			shader.SetMatrix4("modelMatrix", modelMatrix);
			shader.SetFloat("scale", particle.Scale);

			glActiveTexture(GL_TEXTURE0);
			texture.Bind();

			static GLfloat vVertices[] = {
				// Pos      // Tex
				-0.5f, 0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, 1.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f,

				-0.5f, 0.5f, 0.0f, 1.0f,
				0.5f, 0.5f, 1.0f, 1.0f,
				0.5f, -0.5f, 1.0f, 0.0f
			};

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vVertices);
			glEnableVertexAttribArray(0);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
}

void ParticleGenerator::Init()
{
	glBindAttribLocation(shader.ID, 0, "vVertex");

	for (GLuint i = 0; i < MaxAmount; i++)
	{
		Particles.push_back(ParticleObject());
	}
}

GLuint ParticleGenerator::FindUnusedParticle()
{
	static GLuint lastUsedParticle = 0;

	for (GLuint i = lastUsedParticle; i < MaxAmount; i++)
	{
		if (Particles[i].Life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	for (GLuint i = 0; i < lastUsedParticle; i++)
	{
		if (Particles[i].Life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	return -1;
}

void ParticleGenerator::RespawnParticle()
{
	if (!Target)
	{
		std::cout << "[ParticleGenerator] Error, target not found" << std::endl;
		return;
	}

	int index = FindUnusedParticle();

	if (index >= 0)
	{
		ParticleObject &p = Particles[index];

		GLfloat random = ((rand() % 100) - 50) / 10.0f;
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
		p.Color = Vector4(rColor, rColor, rColor, 1.0f);

		p.InitialLifeTime = InitialLifeTime;
		p.Life = InitialLifeTime;

		p.Position = Target->transform.Position + Offset + random;
		p.InitialScale = ParticleSize;
		p.Scale = ParticleSize;

		p.Velocity = Vector2(rand() % (int)(MaxSpeed.x + 1.0f - MinSpeed.x), rand() % (int)(MaxSpeed.y + 1.0f - MinSpeed.y)) + MinSpeed + (-1.0f);
		p.AngularSpeed = rand() % (int)(MaxAngularSpeed + 1.0f) - 0.5f * MaxAngularSpeed - 1.0f;

		p.Mass = ParticleMass;
	}
}

void ParticleGenerator::AddAffectors(std::vector<ParticleAffector*> affectors)
{
	for (ParticleAffector* pa : affectors)
	{
		Affectors.push_back(pa);
	}
}

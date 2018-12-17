#include "Application.h"
#include "ParticleManager.h"
#include "Sprite.h"
#include "ParticleGenerator.h"
#include "ParticleSpawn.h"

SpriteRenderer* Renderer;

ParticleGenerator* RedFlame1;
ParticleGenerator* RedFlame2;
ParticleGenerator* FireGenerator;
ParticleGenerator* GradientGenerator;

ParticleSpawn* FireSource;
ParticleSpawn* RedFlameSource;
ParticleSpawn* GradientSource;

GravityAffector* Particle_GAffector;

Application::Application(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}


Application::~Application()
{
	delete Renderer;
}

void Application::Init()
{
	// Setup orthogonal projection matrix
	Matrix4 projectionMatrix;
	projectionMatrix = Matrix4::ortho(0.0f, static_cast<GLfloat>(this->screenWidth), 0.0f, static_cast<GLfloat>(this->screenHeight), -1.0f, 1.0f);

	// Load shaders
	ParticleManager::LoadShader("../vertexShader.vert", "../fragmentShader.frag", "SpriteShader");
	ParticleManager::LoadShader("../particleVertShader2.vert", "../particleFragShader2.frag", "NormShader");
	ParticleManager::LoadShader("../particleVertShader.vert", "../particleFragShader.frag", "ColorFieldShader");

	// Configure shaders
	ParticleManager::GetShader("SpriteShader").Use().SetInteger("sampler2d", 0);
	ParticleManager::GetShader("SpriteShader").SetMatrix4("projectionMatrix", projectionMatrix);
	ParticleManager::GetShader("NormShader").Use().SetInteger("sampler2d", 0);
	ParticleManager::GetShader("NormShader").SetMatrix4("projectionMatrix", projectionMatrix);
	ParticleManager::GetShader("ColorFieldShader").Use().SetInteger("sampler2d", 0);
	ParticleManager::GetShader("ColorFieldShader").SetMatrix4("projectionMatrix", projectionMatrix);

	// Load textures
	ParticleManager::LoadTexture("../media/Flame.bmp", GL_TRUE, "Flame");
	ParticleManager::LoadTexture("../media/circle.bmp", GL_TRUE, "Circle");
	ParticleManager::LoadTexture("../media/RedFlame.bmp", GL_TRUE, "RedFlame");
	ParticleManager::LoadTexture("../media/GradientColor.bmp", GL_TRUE, "Gradient");

	// Set render-specific controls
	static Shader shader = ParticleManager::GetShader("SpriteShader");
	Renderer = new SpriteRenderer(shader);

	// Create a movable object || stationary object for particles to follow
	FireSource = new ParticleSpawn(Vector2(500.0f, 300.0f), 0.0f, Vector2(1.0f, 1.0f), ParticleManager::GetTexture("Circle"));
	RedFlameSource = new ParticleSpawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.0f, 0.0f), ParticleManager::GetTexture("Circle"));
	GradientSource = new ParticleSpawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.0f, 0.0f), ParticleManager::GetTexture("Circle"));

	// Initializing affectors to be used
	PositionAffector* Particle_PAffector = new PositionAffector();
	GravityAffector* p_GravityAffector = new GravityAffector(Vector2(0.0f, 82.0f));
	Particle_GAffector = new GravityAffector(Vector2(-25.0f, 0.0f));
	RotationAffector* Particle_RAffector = new RotationAffector();
	ScaleDownAffector* Particle_SDAffector = new ScaleDownAffector();

	// Flame from fire particle generators initialization & configuration
	RedFlame1 = new ParticleGenerator(ParticleManager::GetShader("NormShader"), ParticleManager::GetTexture("RedFlame"), 200, RedFlameSource);
	RedFlame2 = new ParticleGenerator(ParticleManager::GetShader("NormShader"), ParticleManager::GetTexture("RedFlame"), 200, RedFlameSource);
	// Flame from fire particle generators configuration
	RedFlame1->Configure(Vector2(100.0f, 0.0f), Vector2(-100.0f, 0.0f), 25.0f, 0.2f, 5.0f, 120.0f);
	RedFlame2->Configure(Vector2(100.0f, 0.0f), Vector2(-100.0f, 0.0f), 25.0f, 0.2f, 5.0f, 120.0f);
	// Flame from fire particle generators affectors
	RedFlame1->AddAffectors({ Particle_PAffector, p_GravityAffector, Particle_RAffector, new ScaleAffector(1.0f), Particle_GAffector });
	RedFlame2->AddAffectors({ Particle_PAffector, p_GravityAffector, Particle_RAffector, new ScaleAffector(0.99f), Particle_GAffector });

	// Fire particle generator initialization
	FireGenerator = new ParticleGenerator(ParticleManager::GetShader("ColorFieldShader"), ParticleManager::GetTexture("Flame"), 500, FireSource);
	// Fire particle generator configuration
	FireGenerator->Configure(Vector2(0.0f, 200.0f), Vector2(0.0f, -10.0f), 280.0f, 0.0f, 1.5f, 0.0f);
	// Fire particle generator extra configuration
	FireGenerator->Offset = Vector2(25.0f, 25.0f);
	FireGenerator->ParticleMass = 0.8f;
	// Fire particle generator affectors
	FireGenerator->AddAffectors({ Particle_PAffector, new FadeAffector(4.0f), Particle_SDAffector, Particle_GAffector });

	// Blue and red box initialization
	GradientGenerator = new ParticleGenerator(ParticleManager::GetShader("NormShader"), ParticleManager::GetTexture("Gradient"), 1000, GradientSource);
	// Blue and red box configuration
	GradientGenerator->Configure(Vector2(100.0f, 100.0f), Vector2(-100.0f, -100.0f), 25.0f, 0.0f, 1.0f, 240.0f);
	// Blue and red box affectors
	GradientGenerator->AddAffectors({ Particle_PAffector, new FadeAffector(0.00000001f/ 10.0f), Particle_SDAffector, Particle_RAffector });
}

void Application::Update(GLfloat deltaTime)
{
	static float timer = 0.0f;
	timer += deltaTime;

	RedFlame1->Update(deltaTime);
	RedFlame2->Update(deltaTime);
	FireGenerator->Update(deltaTime);
	GradientGenerator->Update(deltaTime);

	RedFlameSource->transform.Position = Vector2(320.0f * (1.0f + sinf((rand() % 1000 - 500) / 500.0f)), 110.0f);
	GradientSource->transform.Position = Vector2(480.0f * (1.0f - sinf(2.0f * timer)), 250.0f);
	FireSource->transform.Position = Vector2(320.0f, 110.0f);
}

void Application::ProcessInput(GLFWwindow * window, GLfloat deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		Particle_GAffector->Force.x -= 1.0f;
		std::cout << "Gravity Affector: " << Particle_GAffector->Force.x << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		Particle_GAffector->Force.x += 1.0f;
		std::cout << "Gravity Affector: " << Particle_GAffector->Force.x << std::endl;
	}

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
}

void Application::Render()
{
	// Draw particles	
	RedFlame1->Draw();
	RedFlame2->Draw();
	FireGenerator->Draw();
	GradientGenerator->Draw();
}
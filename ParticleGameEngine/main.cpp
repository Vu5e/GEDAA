#define GLFW_INCLUDE_ES2 1
#define GLFW_DLL 1

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include "Application.h"
#include <fmod.hpp>
#include <fmod_errors.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define TEXTURE_COUNT 13

GLFWwindow* window;

//Must be power of 2
#define SPECTRUM_SIZE 1024
#define SPECTRUM_EXP_2 10

GLint GprogramID = -1;
GLuint GtextureID[TEXTURE_COUNT];

float m_spectrumLeft[SPECTRUM_SIZE];
float m_spectrumRight[SPECTRUM_SIZE];

float m_highestSpectrumLeft[SPECTRUM_SIZE];
float m_highestSpectrumRight[SPECTRUM_SIZE];

float m_highestSpectrum[SPECTRUM_EXP_2];
float m_spectrum[SPECTRUM_EXP_2];

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

//FMOD Error Check
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

FMOD::System* m_fmodSystem;
FMOD::Sound* m_music;
FMOD::Channel* m_musicChannel;

void initFmod()
{
	FMOD_RESULT result;
	unsigned int version;

	result = FMOD::System_Create(&m_fmodSystem);
	ERRCHECK(result);

	result = m_fmodSystem->getVersion(&version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("FMOD Error! You are using an old version of FMOD.", version, FMOD_VERSION);
	}

	//Initialise fmod system
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	//Load and Set up Music
	result = m_fmodSystem->createStream("../media/Song4.mp3", FMOD_SOFTWARE, 0, &m_music);
	ERRCHECK(result);

	//Play the loaded mp3 music
	result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
	ERRCHECK(result);
}

void updateFmod()
{
	m_fmodSystem->update();

	//Get spectrum for left and right stereo channels
	m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
	m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);
}

int main(void)
{
	updateFmod();

	static int mainSpectrum = 2;

	GLint spectrumLoc = glGetUniformLocation(GprogramID, "Factor1");
	if (spectrumLoc != -1)
	{
		glUniform1f(spectrumLoc, m_highestSpectrum[mainSpectrum]);
	}

	if (!glfwInit())
	{
		return -1;
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle System Game Engine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		printf("glfwCreateWindow Error\n");
		exit(1);
	}

	glfwMakeContextCurrent(window);

	double prevTime = 0.0f;
	double currTime = 0.0f;

	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.Init();

	while (!glfwWindowShouldClose(window))
	{
		currTime = clock() / 1000.0f;
		double deltaTime = currTime - prevTime;
		prevTime = currTime;

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		app.ProcessInput(window, deltaTime);
		app.Update(deltaTime);
		app.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

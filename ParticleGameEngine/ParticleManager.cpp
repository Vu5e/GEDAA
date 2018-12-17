#include "ParticleManager.h"

#include "Bitmap.h"
#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D> ParticleManager::Textures;
std::map<std::string, Shader> ParticleManager::Shaders;

Shader ParticleManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader ParticleManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ParticleManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2D ParticleManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ParticleManager::Clear()
{
	// Delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);

	// Delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ParticleManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile)
{
	// Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// Close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();

	// Create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);

	return shader;
}

Texture2D ParticleManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	// Load image
	CBitmap image(file);
	int width = image.GetWidth(), height = image.GetHeight();

	// Generate texture
	texture.Generate(width, height, (unsigned char*)image.GetBits());

	// Free image data
	image.Dispose();

	return texture;
}

#pragma once

#include <map>
#include <string>
#include "Texture2D.h"
#include "Shader.h"

class ParticleManager
{
public:
	// Resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	// Loads vertex, fragment shader source code.
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);

	// Retrieves a stored shader
	static Shader GetShader(std::string name);

	// Loads texture from file
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);

	// Retrieves a stored texture
	static Texture2D GetTexture(std::string name);

	static void Clear();
private:
	ParticleManager() { }

	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);

	// Loads a single texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};


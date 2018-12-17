#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <GLES2\gl2.h>
#include "Vector.h"
#include "Matrix.h"

class Shader
{
public:
	// State
	GLuint ID;

	// Constructor
	Shader() { }

	// Sets the current shader as active
	Shader &Use();

	// Compiles the shader from given source code
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource);

	// Utility functions
	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, const Vector2 &value, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, const Vector3 &value, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, const Vector4 &value, GLboolean useShader = false);
	void SetMatrix4(const GLchar *name, const Matrix4 &matrix, GLboolean useShader = false);

private:
	// Checks if compilation or linking failed and if so, print the error logs
	void CheckCompileErrors(GLuint object, std::string type);
};


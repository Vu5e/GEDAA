#include "Sprite.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::initRenderData()
{
	glBindAttribLocation(shader.ID, 0, "vVertex");
}

void SpriteRenderer::DrawSprite(Texture2D &texture, Vector2 position,
	Vector2 size, GLfloat rotate, Vector3 color)
{
	// Prepare transformations
	this->shader.Use();

	Matrix4 modelMatrix;

	modelMatrix = Matrix4::translate(Vector3(position.x, position.y, 0.0f)) *
		Matrix4::rotate(rotate, Vector3(0.0f, 0.0f, 1.0f)) *
		Matrix4::scale(Vector3(size.x, size.y, 1.0f));

	this->shader.SetMatrix4("modelMatrix", modelMatrix);
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	static GLfloat vVertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
}

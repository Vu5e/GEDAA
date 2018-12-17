#pragma once

#include "texture2D.h"
#include "Shader.h"
#include "Vector.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Texture2D &texture, Vector2 position,
		Vector2 size = Vector2(10.0f, 10.0f), GLfloat rotate = 0.0f,
		Vector3 color = Vector3(1.0f, 1.0f, 1.0f));
private:
	Shader shader;
	//GLuint quadVAO;

	void initRenderData();
};


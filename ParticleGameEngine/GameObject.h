#pragma once

#include "texture2D.h"
#include "Sprite.h"
#include "Vector.h"
#include "Transform.h"

class GameObject
{
public:
	// Object state
	Transform transform;
	Vector2 Velocity;
	Vector3 Color;
	GLboolean IsSolid;
	GLboolean Destroyed;

	// Render state
	Texture2D Sprite;

	// Constructor(s)
	GameObject();
	GameObject(Vector2 pos, Vector2 scale, Texture2D sprite, Vector3 color = Vector3(1.0f, 1.0f, 1.0f), Vector2 velocity = Vector2(0.0f, 0.0f));

	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};


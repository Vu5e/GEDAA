#include "GameObject.h"

GameObject::GameObject()
	: transform(), Velocity(0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(Vector2 pos, Vector2 scale, Texture2D sprite, Vector3 color, Vector2 velocity)
	: transform(pos, scale), Velocity(velocity), Color(color), Sprite(sprite), IsSolid(false), Destroyed(false) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->transform.Position, this->transform.Scale, this->transform.Rotation, this->Color);
}

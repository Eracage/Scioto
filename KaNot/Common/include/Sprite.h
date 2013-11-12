#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <Viewport.h>
#include <Shader.h>
#include <Texture.h>
#include <Sciotomath\Vector.h>
#include <Sciotomath\Rectangle.h>

namespace Scioto
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(Texture2D* texture);
		~Sprite();
		void setTexture(Texture2D* texture);

		void setDepth(float depth);
		void setPosition(Vector2 Position);
		void setSize(Vector2 Size);
		void setRotation(float Radians);

		Vector2 getPosition();

		Vector3 m_position;
		Vector2 m_size;
		float m_radians;

	private:
		Sprite(Sprite& sprite);

		Texture2D* m_texture;
		
		friend class SpriteBatch;
	};
}

#endif
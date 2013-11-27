#pragma once
#ifndef SPRITE_H_SCIOTO
#define SPRITE_H_SCIOTO

#include "Viewport.h"
#include "Shader.h"
#include "Texture.h"
#include "Drawable.h"
#include "Sciotomath\Vector.h"
#include "Sciotomath\Rectangle.h"

namespace Scioto
{
	class Sprite : public Drawable
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

		Vector2 m_size;

	private:
		Sprite(Sprite& sprite);
		void Draw(Shader* shader, float* projection, float* translation, float* rotation, float* scale, GLuint VBO);

		Texture2D* m_texture;
		GLuint VBO;
		
		friend class SpriteBatch;
	};
}

#endif
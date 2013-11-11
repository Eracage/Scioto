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

		void setPosition(Vector2 Position);
		void setSize(Vector2 Size);
		void setRotation(float Radians);

		void setViewport(Viewport* viewport);
		void setShader(Shader* shader);

		void Draw(float z);

		Vector2 m_position, m_size;
		float m_radians;

	private:
		void init();
		void genBuffer();
		Sprite(Sprite& sprite);
		
		float* m_scale;
		float* m_translation;
		float* m_rotation;

		float* Data;

		Viewport* m_viewport;
		Shader* m_shader;

		Texture2D* m_texture;

		GLuint VBO;
		
		friend class SpriteBatch;
	};
}

#endif
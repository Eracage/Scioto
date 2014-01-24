#pragma once
#ifndef ENGINE_H_SCIOTO
#define ENGINE_H_SCIOTO

#include "Debug.h"
#include "Shader.h"
#include "Viewport.h"
#include "FileReader.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Utils.h"
#include <vector>

namespace Scioto
{
	class Object
	{
	public:
		Object(Sprite* sprite, Vector2 speed)
			: m_sprite(sprite),
			  m_speed(speed)
		{}
		~Object()
		{
			delete m_sprite;
		}

		Sprite* m_sprite;
		Vector2 m_speed;
		void update(double dt)
		{
			m_sprite->m_position += m_speed * dt;
			if (checkCollision())
				m_sprite->m_position += m_speed * dt;
		}
		void setPosition(Vector2 pos)
		{
			m_sprite->m_position = pos;
		}
		Vector2 getPosition()
		{
			return m_sprite->getPosition();
		}
		bool checkCollision()
		{
			bool collided = false;
			if (getPosition().x < 0)
			{
				m_speed.x = -m_speed.x;
				collided = true;
			}
			if (getPosition().y < 0)
			{
				m_speed.y = -m_speed.y;
				collided = true;
			}
			if (getPosition().x > 1600)
			{
				m_speed.x = -m_speed.x;
				collided = true;
			}
			if (getPosition().y > 1600)
			{
				m_speed.y = -m_speed.y;
				collided = true;
			}
			return collided;
		}
	};

	class Engine
	{
		public:
			Engine(float ContextWidht, float ContextHeight);
			~Engine();
			void Update();
			void Draw();

			Shader* shader;
			Viewport* viewport;
			SpriteBatch* m_spritebatch;
			Timer* m_timer;
			float m_baseTime;
			
			Texture2D* m_backTexture;
			Sprite* m_background;
			Texture2D* m_texture;
			Texture2D* m_texture2;
			Texture2D* m_texture3;
			std::vector<Object*> m_sprites;
			Object* m_trex;
			float m_trotation;

			Vector2 a;
			Vector2 b;
			Vector2 c;
			Vector2 d;
			Rectangle r;
	};
}
#endif
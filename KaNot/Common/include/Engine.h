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
			std::vector<Sprite*> m_sprites;
			Sprite* m_trex;
			float m_trotation;

			Vector2 a;
			Vector2 b;
			Vector2 c;
			Vector2 d;
			Rectangle r;
	};
}
#endif
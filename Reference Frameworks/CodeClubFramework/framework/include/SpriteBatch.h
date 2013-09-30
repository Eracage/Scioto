/* 
 * @file SpriteBatch.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <vector>

#include <devmath/Matrix.h>
#include <devmath/Rectangle.h>
#include <devmath/Vector2.h>

#include <Graphics.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>
#include <VertexArray.h>
#include <VertexBuffer.h>

namespace glframework
{
	class SpriteBatch
	{
	public:

		SpriteBatch();

		SpriteBatch(Graphics* graphics);

		~SpriteBatch();

		void begin();

		void end();

		void draw(const Texture* texture, const devmath::Rectangle& destination);

		void draw(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source);
		
		void draw(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source, const devmath::Vector2& origin, const float rotationAngle = 0.0f);

		void draw(const Texture* texture, const devmath::Vector2& position);

		void draw(const Texture* texture, const devmath::Vector2& position, const devmath::Rectangle& source);
		
		void draw(const Texture* texture, const devmath::Vector2& position, const devmath::Rectangle& source, const devmath::Vector2& origin, const float rotationAngle = 0.0f);

	private:

		struct Sprite
		{
			devmath::Rectangle source;
			devmath::Vector2 topLeft;
			devmath::Vector2 bottomRight;
			devmath::Vector2 origin;
			const Texture* texture;
			float rotationAngle;
		};

		static const unsigned int MAX_VERTEX_COUNT = 2048;
		static const unsigned int VERTICES_PER_SPRITE = 4;

		Graphics* _graphics;
		
		Shader* _shader;
		VertexBuffer* _vertexBuffer;
		IndexBuffer* _indexBuffer;

		VertexArray* _vertexPositions;
		VertexArray* _vertexTextureCoords;
		unsigned int _vertexOffset;

		devmath::Matrix4 _projectionTransform;

		Sprite* _sprites;
		std::vector<Sprite*> _sortedSprites;
		unsigned int _spriteCount;

		bool _isActive;

		SpriteBatch(const SpriteBatch& spriteBatch);

		void defaults();

		void initialize();
		void destroy();
		void prepareRendering();
		void render();
		void createSprite(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source, const devmath::Vector2& origin, const float rotationAngle = 0.0f);
		void createSprite(const Texture* texture, const devmath::Vector2& position, const devmath::Rectangle& source, const devmath::Vector2& origin, const float rotationAngle = 0.0f);
		void createSprite(const Texture* texture, const devmath::Vector2& topLeft, const devmath::Vector2& bottomRight, const devmath::Rectangle& source, const devmath::Vector2& origin, const float rotationAngle = 0.0f);
		void initializeShader();
		void initializeBuffers();
		void initializeProjectionTransform();
		void initializeSprites();
		void prepareSorting();
		void renderBatch(const Texture* texture, const Sprite* sprites, const int spriteCount);
		void clearBuffers();
		void renderSprite(const Sprite* sprite);
		devmath::Matrix3 createTransform(const Sprite* sprite);
		void createVertexPositions(const Sprite* sprite, const devmath::Matrix3& transform);
		void createVertexTextureCoords(const Sprite* sprite);
		void createIndices();
	};
}

#endif
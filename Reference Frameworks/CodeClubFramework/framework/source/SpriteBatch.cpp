/* 
 * @file SpriteBatch.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <SpriteBatch.h>

#include <cassert>
#include <string>

using namespace devmath;
using namespace glframework;
using namespace std;

SpriteBatch::SpriteBatch()
	: _graphics(NULL)
{
	defaults();
}

SpriteBatch::SpriteBatch(Graphics* graphics)
	: _graphics(graphics)
{
	defaults();
	initialize();
}

SpriteBatch::~SpriteBatch()
{
	destroy();
}


// Public

void SpriteBatch::begin()
{
	assert(!_isActive);

	_isActive = true;
	_spriteCount = 0;
}

void SpriteBatch::end()
{
	assert(_isActive);

	if(_spriteCount > 0)
	{
		prepareSorting();
		prepareRendering();
		render();
	}

	_isActive = false;
}

void SpriteBatch::draw(const Texture* texture, const devmath::Rectangle& destination)
{
	assert(_isActive);
	createSprite(texture, destination, Rectangle::empty(), Vector2::zero());
}

void SpriteBatch::draw(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source)
{
	assert(_isActive);
	createSprite(texture, destination, source, Vector2::zero());
}
		
void SpriteBatch::draw(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source, const Vector2& origin, const float rotationAngle)
{
	assert(_isActive);
	createSprite(texture, destination, source, origin, rotationAngle);
}

void SpriteBatch::draw(const Texture* texture, const Vector2& position)
{
	assert(_isActive);
	createSprite(texture, position, Rectangle::empty(), Vector2::zero());
}

void SpriteBatch::draw(const Texture* texture, const Vector2& position, const devmath::Rectangle& source)
{
	assert(_isActive);
	createSprite(texture, position, source, Vector2::zero());
}
		
void SpriteBatch::draw(const Texture* texture, const Vector2& position, const devmath::Rectangle& source, const Vector2& origin, const float rotationAngle)
{
	assert(_isActive);
	createSprite(texture, position, source, origin, rotationAngle);
}


// Private

void SpriteBatch::defaults()
{
	_shader = NULL;
	_vertexBuffer = NULL;
	_indexBuffer = NULL;

	_vertexPositions = NULL;
	_vertexTextureCoords = NULL;
	_vertexOffset = 0;

	_projectionTransform = Matrix4::identity();

	_sprites = NULL;
	_spriteCount = 0;

	_isActive = false;
}

void SpriteBatch::initialize()
{
	initializeShader();
	initializeBuffers();
	initializeProjectionTransform();
	initializeSprites();
}

void SpriteBatch::destroy()
{
	delete[] _sprites;

	delete _indexBuffer;
	delete _vertexBuffer;
	delete _shader;
}

void SpriteBatch::prepareRendering()
{
	_graphics->setShader(_shader);
	_graphics->setVertexBuffer(_vertexBuffer);
	_graphics->setIndexBuffer(_indexBuffer);
	_graphics->setProjectionTransform(_projectionTransform);
}

void SpriteBatch::render()
{
	vector<Sprite*>::iterator position = _sortedSprites.begin();
	const vector<Sprite*>::iterator endPosition = _sortedSprites.end();

	const Texture* batchTexture = (*position)->texture;
	int spriteCount;

	for(vector<Sprite*>::iterator i = position + 1; i != endPosition; ++i)
	{
		Sprite* sprite = (*i);

		if(sprite->texture != batchTexture)
		{
			spriteCount = i - position;
			renderBatch(batchTexture, *position, spriteCount);

			position = i;
			batchTexture = sprite->texture;
		}
	}

	spriteCount = endPosition - position;
	renderBatch(batchTexture, *position, spriteCount);
}

void SpriteBatch::createSprite(const Texture* texture, const devmath::Rectangle& destination, const devmath::Rectangle& source, const Vector2& origin, const float rotationAngle)
{
	const Vector2 topLeft((float)destination.left(), (float)destination.top());
	const Vector2 bottomRight((float)destination.right(), (float)destination.bottom());

	createSprite(texture, topLeft, bottomRight, source, origin, rotationAngle);
}

void SpriteBatch::createSprite(const Texture* texture, const Vector2& position, const devmath::Rectangle& source, const Vector2& origin, const float rotationAngle)
{
	const float right = position.x + texture->width();
	const float bottom = position.y + texture->height();
	const Vector2 bottomRight(right, bottom);

	createSprite(texture, position, bottomRight, source, origin, rotationAngle);
}

void SpriteBatch::createSprite(const Texture* texture, const Vector2& topLeft, const Vector2& bottomRight, const devmath::Rectangle& source, const Vector2& origin, const float rotationAngle)
{
	Sprite* sprite = &_sprites[_spriteCount];
	sprite->texture = texture;
	sprite->topLeft = topLeft;
	sprite->bottomRight = bottomRight;
	sprite->source = source;
	sprite->origin = origin;
	sprite->rotationAngle = rotationAngle;

	_spriteCount++;
}

void SpriteBatch::initializeShader()
{
	const string vertexCode =
		"attribute vec3 fwPosition;								"
		"attribute vec2 fwTextureCoord;							"

		"uniform mat4 fwProjection;								"
		"varying vec2 textureCoord;								"

		"void main()											"
		"{														"
		"    textureCoord = fwTextureCoord;						"
		"    gl_Position = fwProjection * vec4(fwPosition, 1.0);"
		"}														";

	const string fragmentCode =
		"uniform sampler2D fwSampler;						   "
		"varying vec2 textureCoord;							   "

		"void main()										   "
		"{													   "
		"    gl_FragColor = texture2D(fwSampler, textureCoord);"
		"}													   ";

	_shader = new Shader(vertexCode, fragmentCode);
}

void SpriteBatch::initializeBuffers()
{
	_vertexBuffer = new VertexBuffer();
	_indexBuffer = new IndexBuffer();

	_vertexPositions = new VertexArray("fwPosition", 2, MAX_VERTEX_COUNT);
	_vertexBuffer->addVertexArray(_vertexPositions);

	_vertexTextureCoords = new VertexArray("fwTextureCoord", 2, MAX_VERTEX_COUNT);
	_vertexBuffer->addVertexArray(_vertexTextureCoords);
}

void SpriteBatch::initializeProjectionTransform()
{
	const devmath::Rectangle viewport = _graphics->viewport();

	const float nearZ = 0.0f;
	const float farZ = 1.0f;
	const float depth = farZ - nearZ;

	const float width = (float)viewport.width;
	const float height = (float)viewport.height;
	const float leftRight = (float)(viewport.left() + viewport.right());
	const float topBottom = (float)(viewport.top() + viewport.bottom());

	_projectionTransform = Matrix4
	(
		2.0f / width,		0.0f,				  0.0f,					   0.0f,
		0.0f,				2.0f / -height,		  0.0f,					   0.0f,
		0.0f,				0.0f,				  -2.0f / depth,		   0.0f,
		-leftRight / width, -topBottom / -height, -(nearZ + farZ) / depth, 1.0f
	);
}

void SpriteBatch::initializeSprites()
{
	const unsigned int maxSpriteCount = MAX_VERTEX_COUNT / VERTICES_PER_SPRITE;
	_sprites = new Sprite[maxSpriteCount];
}

void SpriteBatch::prepareSorting()
{
	_sortedSprites.resize(_spriteCount);

	for(size_t i = 0; i < _spriteCount; ++i)
		_sortedSprites[i] = &_sprites[i];
}

void SpriteBatch::renderBatch(const Texture* texture, const Sprite* sprites, const int spriteCount)
{
	clearBuffers();

	for(int i = 0; i < spriteCount; ++i)
		renderSprite(sprites + i);

	texture->bind(_shader);
	_graphics->render();
}

void SpriteBatch::clearBuffers()
{
	_vertexOffset = 0;
	_indexBuffer->clear();
}

void SpriteBatch::renderSprite(const Sprite* sprite)
{
	const Matrix3 transform = createTransform(sprite);

	createVertexPositions(sprite, transform);
	createVertexTextureCoords(sprite);
	createIndices();

	_vertexOffset += VERTICES_PER_SPRITE;
}

Matrix3 SpriteBatch::createTransform(const Sprite* sprite)
{
	const Matrix3 postTranslationTransform = Matrix3::createTranslation(sprite->topLeft);
	const Matrix3 rotationTransform = Matrix3::createRotation(sprite->rotationAngle);

	const Vector2 originPosition = sprite->topLeft + sprite->origin;
	const Matrix3 preTranslationTransform = Matrix3::createTranslation(-originPosition);

	return postTranslationTransform * rotationTransform * preTranslationTransform;
}

void SpriteBatch::createVertexPositions(const Sprite* sprite, const Matrix3& transform)
{
	const float left = sprite->topLeft.x;
	const float right = sprite->bottomRight.x;
	const float top = sprite->topLeft.y;
	const float bottom = sprite->bottomRight.y;

	vector<Vector2> vertices;
	vertices.push_back(Vector2(left, top).transform(transform));
	vertices.push_back(Vector2(left, bottom).transform(transform));
	vertices.push_back(Vector2(right, bottom).transform(transform));
	vertices.push_back(Vector2(right, top).transform(transform));

	_vertexPositions->addVertices(vertices, _vertexOffset);
}

void SpriteBatch::createVertexTextureCoords(const Sprite* sprite)
{
	float left = 0.0f;
	float right = 1.0f;
	float top = 1.0f;
	float bottom = 0.0f;

	if(!sprite->source.isEmpty())
	{
		const Texture* texture = sprite->texture;
		const devmath::Rectangle source = sprite->source;

		left = (float)source.left() / texture->width();
		right = (float)source.right() / texture->width();
		top = -(float)source.top() / texture->height();
		bottom = -(float)source.bottom() / texture->height();
	}

	vector<Vector2> vertices;
	vertices.push_back(Vector2(left, top));
	vertices.push_back(Vector2(left, bottom));
	vertices.push_back(Vector2(right, bottom));
	vertices.push_back(Vector2(right, top));

	_vertexTextureCoords->addVertices(vertices, _vertexOffset);
}

void SpriteBatch::createIndices()
{
	_indexBuffer->addIndex(_vertexOffset);
	_indexBuffer->addIndex(_vertexOffset + 1);
	_indexBuffer->addIndex(_vertexOffset + 2);
	_indexBuffer->addIndex(_vertexOffset);
	_indexBuffer->addIndex(_vertexOffset + 2);
	_indexBuffer->addIndex(_vertexOffset + 3);
}
#include <Sprite.h>

namespace Scioto
{
	Sprite::Sprite()
		: m_texture(NULL),
		  m_radians(0)
	{
	}
	Sprite::Sprite(Texture2D* texture)
		: m_radians(0)
	{
		setTexture(texture);
	}
	Sprite::~Sprite(){}

	void Sprite::setTexture(Texture2D* texture)
	{
		m_texture = texture;
		setSize(Vector2(texture->width,texture->height));
	}
	
	void Sprite::setDepth(float depth)
	{
		m_position.z = depth;
	}
	void Sprite::setPosition(Vector2 Position)
	{
		m_position.x = Position.x;
		m_position.y = Position.y;
	}
	void Sprite::setSize(Vector2 Size)
	{
		m_size = Size;
	}
	void Sprite::setRotation(float Radians)
	{
		m_radians = Radians;
	}
	
	Vector2 Sprite::getPosition()
	{
		return Vector2(m_position.x, m_position.y);
	}
}
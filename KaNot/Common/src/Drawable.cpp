#include "Drawable.h"

namespace Scioto
{
	
	Drawable::Drawable(Sprite* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawSprite)
	{
	}
	Drawable::Drawable(Vector2* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector2)
	{
	}
	Drawable::Drawable(Vector3* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector3)
	{
	}
	Drawable::Drawable(Rectangle* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawRectangle)
	{
	}

	Drawable::~Drawable()
	{}

}
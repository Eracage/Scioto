#include "Drawable.h"

namespace Scioto
{
	
	Drawable::Drawable(Sprite* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawSprite),
		  m_depth(depth)
	{
	}
	Drawable::Drawable(Vector2* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector2),
		  m_depth(depth)
	{
	}
	Drawable::Drawable(Vector3* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector3),
		  m_depth(depth)
	{
	}
	Drawable::Drawable(Rectangle* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawRectangle),
		  m_depth(depth)
	{
	}

	Drawable::~Drawable()
	{}

}
#include "Drawable.h"

namespace Scioto
{
	
	Drawable::Drawable()
		: m_shader(1),
		  m_rotation(0.0f),
		  m_scale(1,1),
		  m_position(Vector2()),
		  m_object(nullptr),
		  m_type(External),
		  m_depth(0.0f),
		  m_color(Vector4(1,1,1,1))
	{
	}
	Drawable::Drawable(Vector2* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth, Vector4 color)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector2),
		  m_depth(depth),
		  m_color(color)
		  
	{
	}
	Drawable::Drawable(Vector3* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth,Vector4 color)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawVector3),
		  m_depth(depth),
		  m_color(color)
	{
	}
	Drawable::Drawable(Rectangle* pointer,Vector2 position,Vector2 scale,
		float rotation,int shader,float depth,Vector4 color)
		: m_shader(shader),
		  m_rotation(rotation),
		  m_scale(scale),
		  m_position(position),
		  m_object(pointer),
		  m_type(DrawRectangle),
		  m_depth(depth),
		  m_color(color)
	{
	}

	Drawable::~Drawable()
	{}

	void Drawable::Draw(const Shader* shader, const Matrix4 projection, const Matrix4 translation, const Matrix4 rotation, const Matrix4 scale, GLuint VBO)
	{}
}
#include "SpriteBatch.h"

namespace Scioto
{
	
	SpriteBatch::SpriteBatch(Shader* shader0,Viewport* viewport)
		: m_viewport (viewport)
	{
		m_shaders.push_back(shader0);

	}

	SpriteBatch::~SpriteBatch()
	{}

	
	void SpriteBatch::Draw(Sprite* sprite, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		m_drawables.push_back(new Drawable(sprite,position,scale,rotation,shader,depth));
	}
	void SpriteBatch::Draw(Vector2* vector2, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		m_drawables.push_back(new Drawable(vector2,position,scale,rotation,shader,depth));
	}
	void SpriteBatch::Draw(Vector3* vector3, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		m_drawables.push_back(new Drawable(vector3,position,scale,rotation,shader,depth));
	}
	void SpriteBatch::Draw(Rectangle* rectangle, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		m_drawables.push_back(new Drawable(rectangle,position,scale,rotation,shader,depth));
	}

	void SpriteBatch::Render()
	{

	}

	int SpriteBatch::addShader(Shader* shader)
	{
		m_shaders.push_back(shader);
		return m_shaders.size();
	}
	
	void SpriteBatch::genBuffers(){}

}
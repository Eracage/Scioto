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

	
	void Draw(Sprite* sprite, Vector2 position,Vector2 scale,
		float rotation,int shader);
	void Draw(Vector2* vector2, Vector2 position,Vector2 scale,
		float rotation,int shader);
	void Draw(Vector3* vector3, Vector2 position,Vector2 scale,
		float rotation,int shader);
	void Draw(Rectangle* rectangle, Vector2 position,Vector2 scale,
		float rotation,int shader);

	void Render();

	int addShader(Shader* shader);

}
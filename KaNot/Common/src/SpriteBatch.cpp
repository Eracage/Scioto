#include "SpriteBatch.h"

namespace Scioto
{
	
	SpriteBatch::SpriteBatch(Shader* shader0,Viewport* viewport)
		: m_viewport (viewport)
	{
		m_shaders.push_back(shader0);
		Init();
	}

	SpriteBatch::~SpriteBatch()
	{}

	void SpriteBatch::Init()
	{
		m_translation = (float*)calloc(16,sizeof(float));
		m_rotation = (float*)calloc(16,sizeof(float));
		m_scale = (float*)calloc(16,sizeof(float));

		setScale(Vector2(1,1));
		setRotation(0);
		setTranslation(Vector3());
	}

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
		Sort();
		for(int i=0;i<m_drawables.size();i++)
		{
			AddDraw(m_drawables[i]);
		}
	}

	int SpriteBatch::addShader(Shader* shader)
	{
		m_shaders.push_back(shader);
		return m_shaders.size();
	}

	//Private

	void SpriteBatch::setScale(Vector2 scale)
	{
		if (scale == m_last_scale)
			return;
		
		m_scale[0] = scale.x;
		m_scale[5] = scale.y;
		m_scale[10] = 1;
		m_scale[15] = 1;

		m_last_scale = scale;
	}

	void SpriteBatch::setTranslation(Vector3 position)
	{
		if (position == m_last_position)
			return;

		m_translation[0] = 1;
		m_translation[3] = (int)position.x;
		m_translation[5] = 1;
		m_translation[7] = (int)-position.y;
		m_translation[10] = 1;
		m_translation[11] = (int)position.z;
		m_translation[15] = 1;

		m_last_position = position;
	}

	void SpriteBatch::setRotation(float rotation)
	{
		if(rotation == m_last_rotation)
			return;

		m_rotation[0] = std::cos(-rotation);
		m_rotation[1] = -std::sin(-rotation);
		m_rotation[4] = std::sin(-rotation);
		m_rotation[5] = std::cos(-rotation);
		m_rotation[10] = 1;
		m_rotation[15] = 1;

		m_last_rotation = rotation;
	}
	
	void SpriteBatch::genBuffers()
	{
#pragma region Sprite
		{
			glGenBuffers(1,&VBOs[Drawable::DrawableType::DrawSprite]);
		
			float* Data = (float*)malloc(30*sizeof(float));

			Data[0] = -0.5f; 
			Data[1] = -0.5f; 
			Data[2] = 0; 

			Data[3] = 0; 
			Data[4] = 0; 


			Data[5] = -0.5f; 
			Data[6] = 0.5f; 
			Data[7] = 0;

			Data[8] = 0; 
			Data[9] = 1; 


			Data[10] = 0.5f; 
			Data[11] = -0.5f; 
			Data[12] = 0; 

			Data[13] = 1; 
			Data[14] = 0; 
    

			Data[15] = -0.5f; 
			Data[16] = 0.5f; 
			Data[17] = 0; 

			Data[18] = 0; 
			Data[19] = 1; 


			Data[20] = 0.5f; 
			Data[21] = 0.5f; 
			Data[22] = 0; 

			Data[23] = 1; 
			Data[24] = 1; 


			Data[25] = 0.5f; 
			Data[26] = -0.5f; 
			Data[27] = 0; 

			Data[28] = 1; 
			Data[29] = 0; 
	
			glBindBuffer(GL_ARRAY_BUFFER,VBOs[Drawable::DrawableType::DrawSprite]); 
  
			glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW); 
			free(Data);
		}
#pragma endregion

#pragma region Vector
		{
			glGenBuffers(1,&VBOs[Drawable::DrawableType::DrawVector2]);
		
			float* Data = (float*)malloc(30*sizeof(float));

			Data[0] = -0.5f; 
			Data[1] = -0.5f; 
			Data[2] = 0; 

			Data[3] = 0; 
			Data[4] = 0; 


			Data[5] = -0.5f; 
			Data[6] = 0.5f; 
			Data[7] = 0;

			Data[8] = 0; 
			Data[9] = 1; 


			Data[10] = 0.5f; 
			Data[11] = -0.5f; 
			Data[12] = 0; 

			Data[13] = 1; 
			Data[14] = 0; 
    

			Data[15] = -0.5f; 
			Data[16] = 0.5f; 
			Data[17] = 0; 

			Data[18] = 0; 
			Data[19] = 1; 


			Data[20] = 0.5f; 
			Data[21] = 0.5f; 
			Data[22] = 0; 

			Data[23] = 1; 
			Data[24] = 1; 


			Data[25] = 0.5f; 
			Data[26] = -0.5f; 
			Data[27] = 0; 

			Data[28] = 1; 
			Data[29] = 0; 
	
			glBindBuffer(GL_ARRAY_BUFFER,VBOs[Drawable::DrawableType::DrawVector2]); 
  
			glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW); 
			free(Data);
		}
#pragma endregion
	}

	void SpriteBatch::Sort(){}

	void SpriteBatch::AddDraw(Drawable* drawable)
	{
		switch (drawable->m_type)
		{
		case Drawable::DrawableType::DrawSprite:
			//how to draw sprite
			glEnableVertexAttribArray(m_shaders[1]->Position);
			glEnableVertexAttribArray(m_shaders[1]->Uv);
			glUseProgram(m_shaders[1]->Program);

			glDepthFunc(GL_LEQUAL);
			glEnable(GL_DEPTH_TEST);

			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, drawable->m_object.m_sprite->m_texture->GetGLTextureID());

			glUniform1i(m_shaders[1]->loc, 0); 

			glVertexAttribPointer(m_shaders[1]->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
			glVertexAttribPointer(m_shaders[1]->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
			glUniformMatrix4fv(m_shaders[1]->loc2,1,GL_FALSE,m_viewport->m_projection);
			glUniformMatrix4fv(m_shaders[1]->loc3,1,GL_FALSE,m_translation);
			glUniformMatrix4fv(m_shaders[1]->loc4,1,GL_FALSE,m_rotation);
			glUniformMatrix4fv(m_shaders[1]->loc5,1,GL_FALSE,m_scale);
			glBindBuffer(GL_ARRAY_BUFFER,VBOs[Drawable::DrawableType::DrawSprite]); 
			glDrawArrays(GL_TRIANGLES,0,6); 
			glDisableVertexAttribArray(m_shaders[1]->Position);    
			glDisableVertexAttribArray(m_shaders[1]->Uv);   

			break;
		case Drawable::DrawableType::DrawVector2:
			break;
		case Drawable::DrawableType::DrawVector3:
			break;
		case Drawable::DrawableType::DrawRectangle:
			break;
		}
	
	}

}
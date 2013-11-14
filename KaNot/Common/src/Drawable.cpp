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
		  m_depth(0.0f)
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

	void Drawable::Draw(Shader* shader, float* projection, float* translation, float* rotation, float* scale, GLuint VBO)
	{
		glEnableVertexAttribArray(shader->Position);
		glEnableVertexAttribArray(shader->Uv);
		glUseProgram(shader->Program);

		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, m_texture->GetGLTextureID());

		glUniform1i(shader->loc, 0); 

		glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
		glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
		glUniformMatrix4fv(shader->loc2,1,GL_FALSE,projection);
		glUniformMatrix4fv(shader->loc3,1,GL_FALSE,translation);
		glUniformMatrix4fv(shader->loc4,1,GL_FALSE,rotation);
		glUniformMatrix4fv(shader->loc5,1,GL_FALSE,scale);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glDrawArrays(GL_TRIANGLES,0,6);
		glDisableVertexAttribArray(shader->Position);
		glDisableVertexAttribArray(shader->Uv);
	}
}
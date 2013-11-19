#include <Sprite.h>

namespace Scioto
{
	Sprite::Sprite()
		: Drawable(),
		  m_texture(NULL)
	{
	}
	Sprite::Sprite(Texture2D* texture)
		: Drawable()
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
		m_depth = depth;
	}
	void Sprite::setPosition(Vector2 Position)
	{
		m_position = Position;
	}
	void Sprite::setSize(Vector2 Size)
	{
		m_size = m_scale = Size;
	}
	void Sprite::setRotation(float Radians)
	{
		m_rotation = Radians;
	}
	
	Vector2 Sprite::getPosition()
	{
		return m_position;
	}

	void Sprite::Draw(Shader* shader, float* projection, float* translation, float* rotation, float* scale, GLuint VBO)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetGLTextureID());
			
		glUseProgram(shader->Program);
		glEnableVertexAttribArray(glGetAttribLocation(shader->Program,"vPosition"));
		glEnableVertexAttribArray(glGetAttribLocation(shader->Program,"vUv"));

		glUniform1i(
			glGetUniformLocation(shader->Program,"s_texture"), 
			0);

		glGetUniformLocation(shader->Program,"s_texture");

		glVertexAttribPointer(
			glGetAttribLocation(shader->Program,"vPosition"),
			3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
		glVertexAttribPointer(
			glGetAttribLocation(shader->Program,"vUv"),
			2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3));

		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Projection"),
			1,GL_FALSE,projection);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Translation"),
			1,GL_FALSE,translation);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Rotation"),
			1,GL_FALSE,rotation);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Scale"),
			1,GL_FALSE,scale);

		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glDrawArrays(GL_TRIANGLES,0,6);

		glDisableVertexAttribArray(glGetAttribLocation(shader->Program,"vPosition"));
		glDisableVertexAttribArray(glGetAttribLocation(shader->Program,"vUv"));
	}
}
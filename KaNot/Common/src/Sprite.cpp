#include <Sprite.h>
#include <Sciotomath\Matrix4.h>

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

		glGenBuffers(1,&VBO);
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
		
			//float* Data = (float*)malloc(30*sizeof(float));

			//Data[0] = -0.5f; 
			//Data[1] = -0.5f; 
			//Data[2] = 0; 

			//Data[3] = 0; 
			//Data[4] = 0; 


			//Data[5] = -0.5f; 
			//Data[6] = 0.5f; 
			//Data[7] = 0;

			//Data[8] = 0; 
			//Data[9] = 1; 


			//Data[10] = 0.5f; 
			//Data[11] = -0.5f; 
			//Data[12] = 0; 

			//Data[13] = 1; 
			//Data[14] = 0; 
   // 

			//Data[15] = -0.5f; 
			//Data[16] = 0.5f; 
			//Data[17] = 0; 

			//Data[18] = 0; 
			//Data[19] = 1; 


			//Data[20] = 0.5f; 
			//Data[21] = 0.5f; 
			//Data[22] = 0; 

			//Data[23] = 1; 
			//Data[24] = 1; 


			//Data[25] = 0.5f; 
			//Data[26] = -0.5f; 
			//Data[27] = 0; 

			//Data[28] = 1; 
			//Data[29] = 0; 
	
			//glBindBuffer(GL_ARRAY_BUFFER,VBO); 
  
			//glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW); 
			//free(Data);





		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetGLTextureID());

		Vector4 pos(0.5f,0.5f,0.f,1.f);
		
		Matrix4* identity = new Matrix4();
		float* nothing = identity->FirstElement();
		Matrix4 proj(projection);
		Matrix4 trans(translation);
		Matrix4 rotat(rotation);
		Matrix4 scal(scale);
		pos *= scal;
		pos *= rotat;
		pos *= trans;
		pos *= proj;

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
			1,GL_FALSE,proj.FirstElement());
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Translation"),
			1,GL_FALSE,nothing);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Rotation"),
			1,GL_FALSE,nothing);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->Program, "Scale"),
			1,GL_FALSE,scal.FirstElement());

		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glDrawArrays(GL_TRIANGLES,0,6);

		glDisableVertexAttribArray(glGetAttribLocation(shader->Program,"vPosition"));
		glDisableVertexAttribArray(glGetAttribLocation(shader->Program,"vUv"));
	}
}
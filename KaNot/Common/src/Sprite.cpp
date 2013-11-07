#include <Sprite.h>

namespace Scioto
{
	Sprite::Sprite()
		: m_texture(NULL)
	{
		init();
	}
	Sprite::Sprite(Texture2D* texture)
	{
		init();
		setTexture(texture);
	}
	Sprite::~Sprite(){}
	void Sprite::setTexture(Texture2D* texture)
	{
		m_texture = texture;
		setSize(Vector2(texture->width,texture->height));
	}

	
	void Sprite::setPosition(Vector2 Position)
	{
		m_position = Position;

		m_translation[0] = 1;
		m_translation[3] = (int)Position.x;
		m_translation[5] = 1;
		m_translation[7] = (int)-Position.y;
		m_translation[10] = 1;
		m_translation[15] = 1;
	}
	void Sprite::setSize(Vector2 Size)
	{
		m_size = Size;
		
		m_scale[0] = Size.x;
		m_scale[5] = Size.y;
		m_scale[10] = 1;
		m_scale[15] = 1;
	}
	void Sprite::setRotation(float Radians)
	{
		m_radians = Radians;
		
		m_rotation[0] = std::cos(-Radians);
		m_rotation[1] = -std::sin(-Radians);
		m_rotation[4] = std::sin(-Radians);
		m_rotation[5] = std::cos(-Radians);
		m_rotation[10] = 1;
		m_rotation[15] = 1;
	}

	void Sprite::setViewport(Viewport* viewport)
	{
		m_viewport = viewport;
	}
	void Sprite::setShader(Shader* shader)
	{
		m_shader = shader;
	}


	
	void Sprite::init()
	{
		m_translation = (float*)calloc(16,sizeof(float));
		m_rotation = (float*)calloc(16,sizeof(float));
		m_scale = (float*)calloc(16,sizeof(float));
		
		glGenBuffers(1,&VBO);
		genBuffer();
		setPosition(Vector2());
		setRotation(0);
	}

	void Sprite::genBuffer()
	{
		Data = (float*)malloc(30*sizeof(float));

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
	
		glBindBuffer(GL_ARRAY_BUFFER,VBO); 
  
		glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW); 
		free(Data);
	}


	
	void Sprite::Draw(float z)
	{
		glEnableVertexAttribArray(m_shader->Position);
		glEnableVertexAttribArray(m_shader->Uv);
		glUseProgram(m_shader->Program);

		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_translation[11] = z;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetGLTextureID());

		glUniform1i(m_shader->loc, 0); 

		glVertexAttribPointer(m_shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
		glVertexAttribPointer(m_shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
		glUniformMatrix4fv(m_shader->loc2,1,GL_FALSE,m_viewport->m_projection);
		glUniformMatrix4fv(m_shader->loc3,1,GL_FALSE,m_translation);
		glUniformMatrix4fv(m_shader->loc4,1,GL_FALSE,m_rotation);
		glUniformMatrix4fv(m_shader->loc5,1,GL_FALSE,m_scale);
		glBindBuffer(GL_ARRAY_BUFFER,VBO); 
		glDrawArrays(GL_TRIANGLES,0,6); 
		glDisableVertexAttribArray(m_shader->Position);    
		glDisableVertexAttribArray(m_shader->Uv);   
	}

}
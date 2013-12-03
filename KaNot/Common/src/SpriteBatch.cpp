#include "SpriteBatch.h"

namespace Scioto
{
	
	SpriteBatch::SpriteBatch(Viewport* viewport)
		: m_viewport (viewport)
	{
		
		// Making default shader
		const char gVertexShader0[] = 
		"attribute vec3 vPosition;\n"
		"uniform mat4 Projection;\n"
		"uniform mat4 Translation;\n"
		"uniform mat4 Scale;\n"
		"uniform mat4 Rotation;\n"
		"varying vec4 color;\n"
		"void main() {\n"
		"  gl_Position = vec4(vPosition,1.0);\n"
		"  gl_Position *= Scale;\n"	
		"  gl_Position *= Rotation;\n"	
		"  gl_Position *= Translation;\n"	
		"  gl_Position *= Projection;\n"

		"  color = vec4(0.9f,1.0f,0.4f,1.0f);\n"
		"}\n";

		const char gFragmentShader0[] = 
		"varying vec4 color;\n"
		"void main() {\n"
		"  gl_FragColor = color;\n"
		"}\n";
		
		m_shaders.push_back(new Shader(gVertexShader0,gFragmentShader0));


		// Making default sprite shader
		const char gVertexShader1[] = 
		"attribute vec3 vPosition;\n"
		"attribute vec2 vUv;\n"
		"uniform mat4 Projection;\n"
		"uniform mat4 Translation;\n"
		"uniform mat4 Scale;\n"
		"uniform mat4 Rotation;\n"
		"varying vec2 Uv;\n"
		"void main() {\n"
		"  gl_Position = vec4(vPosition,1.0);\n"
		"  gl_Position *= Scale;\n"	
		"  gl_Position *= Rotation;\n"	
		"  gl_Position *= Translation;\n"	
		"  gl_Position *= Projection;\n"	
		"  Uv = vUv;\n"
		"}\n";

		const char gFragmentShader1[] = 
		"varying vec2 Uv;\n"
		"uniform sampler2D s_texture;\n"
		"void main() {\n"
		"  gl_FragColor = texture2D(s_texture,Uv);\n"
		"}\n";
		
		m_shaders.push_back(new Shader(gVertexShader1,gFragmentShader1));


		Init();
	}

	SpriteBatch::~SpriteBatch()
	{}

	void SpriteBatch::Init()
	{
		genBuffers();

		setScale(Vector2(1,1));
		setRotation(0);
		setTranslation(Vector3());
	}

	void SpriteBatch::Draw(Drawable* drawable)
	{
		m_drawables.push_back(drawable);
	}
	void SpriteBatch::Draw(Vector2* vector2, float depth, Vector2 position,
		float scale,float rotation,int shader)
	{
		const float vecLenght = vector2->getLenght();
		const Vector2 scaleVec = Vector2(vecLenght,vecLenght*scale);
		const float vecRotation = vector2->getAngle() * PI / 180;

		Drawable* d = new Drawable(vector2,position,scaleVec,vecRotation,shader,depth);
		m_onceDrawables.push_back(d);
		m_drawables.push_back(d);
	}
	void SpriteBatch::Draw(Vector3* vector3, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		Drawable* d = new Drawable(vector3,position,scale,rotation,shader,depth);
		m_onceDrawables.push_back(d);
		m_drawables.push_back(d);
	}
	void SpriteBatch::Draw(Rectangle* rectangle, float depth, Vector2 position,
		Vector2 scale,float rotation,int shader)
	{
		Drawable* d = new Drawable(rectangle,position,scale,rotation,shader,depth);
		m_onceDrawables.push_back(d);
		m_drawables.push_back(d);
	}

	void SpriteBatch::Render()
	{
		Sort();
		for(int i=0;i<m_drawables.size();i++)
		{
			AddDraw(m_drawables[i]);
		}

		for(int i=0;i<m_onceDrawables.size();i++)
			delete m_onceDrawables[i];

		m_drawables.clear();
		m_onceDrawables.clear();
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
		
		m_scale[0][0] = scale.x;
		m_scale[1][1] = scale.y;
		m_scale[2][2] = 1;
		m_scale[3][3] = 1;

		m_last_scale = scale;
	}

	void SpriteBatch::setTranslation(Vector2 position, float depth)
	{
		setTranslation(Vector3(position.x,position.y,depth));
	}
	void SpriteBatch::setTranslation(Vector3 position)
	{
		if (position == m_last_position)
			return;

		m_translation[0][0] = 1;
		m_translation[0][3] = (int)position.x;
		m_translation[1][1] = 1;
		m_translation[1][3] = (int)-position.y;
		m_translation[2][2] = 1;
		m_translation[2][3] = (int)position.z;
		m_translation[3][3] = 1;

		m_last_position = position;
	}

	void SpriteBatch::setRotation(float rotation)
	{
		if(rotation == m_last_rotation)
			return;

		m_rotation[0][0] = std::cos(-rotation);
		m_rotation[0][1] = -std::sin(-rotation);
		m_rotation[1][0] = std::sin(-rotation);
		m_rotation[1][1] = std::cos(-rotation);
		m_rotation[2][2] = 1;
		m_rotation[3][3] = 1;

		m_last_rotation = rotation;
	}
	
	void SpriteBatch::genBuffers()
	{
		for(int i=0;i<5;i++)
			VBOs.push_back(0);
#pragma region Sprite
		{
			glGenBuffers(1,&VBOs[Drawable::DrawableType::External]);
		
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
	
			glBindBuffer(GL_ARRAY_BUFFER,VBOs[Drawable::DrawableType::External]); 
  
			glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW); 
			free(Data);
		}
#pragma endregion

#pragma region Vector
		{
			glGenBuffers(1,&VBOs[Drawable::DrawableType::DrawVector2]);
		
			float* Data = (float*)malloc(36*sizeof(float));

			// 1
			Data[0]  = 0.0f;
			Data[1]  = 0.0f;
			Data[2]  = 0.0f;

			Data[3]  = -0.1f;
			Data[4]  = 0.3f;
			Data[5]  = 0.0f;

			Data[6]  = 1.0f;
			Data[7]  = 0.0f;
			Data[8]  = 0.0f;

			// 2
			Data[9]  = 0.0f;
			Data[10] = 0.0f;
			Data[11] = 0.0f;

			Data[12] = 1.0f;
			Data[13] = 0.0f;
			Data[14] = 0.0f;

			Data[15] = -0.1f;
			Data[16] = -0.3f;
			Data[17] = 0.0f;

			// 3
			Data[18] = 0.8f;
			Data[19] = 0.0f;
			Data[20] = 0.0f;

			Data[21] = 0.75f;
			Data[22] = 0.3f;
			Data[23] = 0.0f;

			Data[24] = 1.0f;
			Data[25] = 0.0f;
			Data[26] = 0.0f;

			// 4
			Data[27] = 0.8f;
			Data[28] = 0.0f;
			Data[29] = 0.0f;

			Data[30] = 1.0f;
			Data[31] = 0.0f;
			Data[32] = 0.0f;

			Data[33] = 0.8f;
			Data[34] = -0.3f;
			Data[35] = 0.0f;
	
			glBindBuffer(GL_ARRAY_BUFFER,VBOs[Drawable::DrawableType::DrawVector2]); 
  
			glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*36,Data,GL_DYNAMIC_DRAW); 
			free(Data);
		}
#pragma endregion
	}

	void SpriteBatch::Sort(){}

	void SpriteBatch::AddDraw(Drawable* drawable)
	{
		
		const Shader* shader = m_shaders[drawable->m_shader];

		switch (drawable->m_type)
		{
		case Drawable::DrawableType::External:
			//how to draw sprite

			setTranslation(drawable->m_position,drawable->m_depth);
			setScale(drawable->m_scale);
			setRotation(drawable->m_rotation);

			glDepthFunc(GL_LEQUAL);
			glEnable(GL_DEPTH_TEST);

			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			drawable->Draw(shader,m_viewport->m_projection,m_translation,m_rotation, m_scale,VBOs[drawable->m_type]);
			
			break;
		case Drawable::DrawableType::DrawVector2:
			{
				setTranslation(drawable->m_position,drawable->m_depth);
				setScale(drawable->m_scale);
				setRotation(drawable->m_rotation);
			
				glDepthFunc(GL_LEQUAL);
				glEnable(GL_DEPTH_TEST);

				glDisable (GL_BLEND);
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
				glUseProgram(shader->Program);
				glBindBuffer(GL_ARRAY_BUFFER,VBOs[drawable->m_type]);
				glEnableVertexAttribArray(glGetAttribLocation(shader->Program,"vPosition"));
				
				glVertexAttribPointer(
					glGetAttribLocation(shader->Program,"vPosition"),
					3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);
				
				glUniformMatrix4fv(
					glGetUniformLocation(shader->Program, "Projection"),
					1,GL_FALSE,m_viewport->m_projection.FirstElement());
				glUniformMatrix4fv(
					glGetUniformLocation(shader->Program, "Translation"),
					1,GL_FALSE,m_translation.FirstElement());
				glUniformMatrix4fv(
					glGetUniformLocation(shader->Program, "Rotation"),
					1,GL_FALSE,m_rotation.FirstElement());
				glUniformMatrix4fv(
					glGetUniformLocation(shader->Program, "Scale"),
					1,GL_FALSE,m_scale.FirstElement());
				
				glDrawArrays(GL_TRIANGLES,0,12);

				glDisableVertexAttribArray(glGetAttribLocation(shader->Program,"vPosition"));
				glBindBuffer(GL_ARRAY_BUFFER,0);
			}
			break;
		case Drawable::DrawableType::DrawVector3:
			break;
		case Drawable::DrawableType::DrawRectangle:
			break;
		}
	
	}

}
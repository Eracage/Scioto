#include <Engine.h>
#include <stdlib.h>

namespace Scioto
{
	Engine::Engine(float ContextWidht, float ContextHeight)
	{
		const char gVertexShader[] = 
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

		const char gFragmentShader[] = 
		"precision mediump float;\n"
		"varying vec2 Uv;\n"
		"uniform sampler2D s_texture;\n"
		"void main() {\n"
		"  gl_FragColor = texture2D(s_texture,Uv);\n"
		"}\n";

		shader = new Shader(gVertexShader,gFragmentShader);
		viewport = new Viewport(800,800,ContextWidht, ContextHeight);
	
		m_backTexture = new Texture2D("Background.tga");
		m_background = new Sprite(m_backTexture);
		m_background->setShader(shader);
		m_background->setViewport(viewport);
		m_background->setSize(Vector2(ContextWidht*4,ContextHeight*4));
		m_background->setPosition(Vector2(ContextWidht,ContextHeight));

		m_texture = new Texture2D("SciotoLogo.tga");
		m_texture2 = new Texture2D("Test.tga");
		for (int i=0; i<1000;i++)
		{
			if (i%2)
				m_sprites[i] = new Sprite(m_texture);
			else
				m_sprites[i] = new Sprite(m_texture2);
			m_sprites[i]->setShader(shader);
			m_sprites[i]->setViewport(viewport);
			m_sprites[i]->setPosition(Vector2((rand()%1600),(rand()%1600)));
		}
	}
	Engine::~Engine()
	{
	}

	void Engine::Update()
	{
		for (int i=0; i<1000; i++)
		{
			m_sprites[i]->setPosition(m_sprites[i]->m_position+Vector2(
				(rand()%2001-1000)/(i+1),
				(rand()%2001-1000)/(i+1)
				));
		}
	}

	void Engine::Draw()
	{
		checkGlError("draw");

		//Draw
		glClearColor(0,0,0,1);
		#ifdef _WIN32
		glClearDepth(1);
		#else
		glClearDepthf(1);
		#endif

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		m_background->Draw(1);
		for (int i=0; i<1000;i++)
			m_sprites[i]->Draw(0);
	}
}
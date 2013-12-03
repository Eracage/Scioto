#include <Engine.h>
#include <stdlib.h>

namespace Scioto
{
	Engine::Engine(float ContextWidht, float ContextHeight)
	{
		viewport = new Viewport(800,800,ContextWidht, ContextHeight);
		m_spritebatch = new SpriteBatch(viewport);

		m_timer = new Timer();
		
		// Temp
		m_backTexture = new Texture2D("Background.tga");
		m_background = new Sprite(m_backTexture);
		m_background->setSize(Vector2(1000000,1000000));
		m_background->setPosition(Vector2(ContextWidht,ContextHeight));


		m_texture = new Texture2D("SciotoLogo.tga");
		m_texture2 = new Texture2D("Test.tga");
		for (int i=0; i<6000;i++)
		{
			if (i%2)
				m_sprites.push_back(new Sprite(m_texture));
			else
				m_sprites.push_back(new Sprite(m_texture2));
			m_sprites[i]->setPosition(Vector2((rand()%1600),(rand()%1600)));
		}

		m_trotation = 0;
		m_texture3 = new Texture2D("trex.tga");
		m_trex = new Sprite(m_texture3);
		m_trex->setPosition(Vector2(1800,1800));

		a = Vector2(800,800);
		b = Vector2(500,-500);
		c = Vector2(0,800);
		d = Vector2(-800,200);
	}
	Engine::~Engine()
	{
	}

	void Engine::Update()
	{
		double deltaTime = m_timer->GetDeltaTime();
		LOGI("%.5f	%.5f",deltaTime, m_timer->GetCurTime());


		m_trotation += 0.1;
		m_spritebatch->Draw(m_background);


		for (int i=0; i<m_sprites.size(); i++)
		{
			m_sprites[i]->setPosition(m_sprites[i]->getPosition()+Vector2(
				(rand()%80001-40000)/(i+1),
				(rand()%80001-40000)/(i+1)
				));
			m_spritebatch->Draw(m_sprites[i]);
		}
		m_trex->setPosition(m_trex->getPosition() + Vector2(-2,-2));
		if (m_trotation < 0.5)
			m_trex->setRotation(m_trotation);
		else if (m_trotation < 1.5)
			m_trex->setRotation(1-m_trotation);
		else
			m_trotation = -0.5;
		m_spritebatch->Draw(m_trex);
		
		m_spritebatch->Draw(&a,0.0f);
		m_spritebatch->Draw(&b,0.0f,a);
		m_spritebatch->Draw(&c,0.0f,a+b);
		m_spritebatch->Draw(&d,0.0f,a+b+c);

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

		m_spritebatch->Render();
	}
}
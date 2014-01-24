#include <Engine.h>
#include <stdlib.h>


namespace Scioto
{

	Engine::Engine(float ContextWidht, float ContextHeight)
	{
		viewport = new Viewport(1600,1600,ContextWidht, ContextHeight);
		m_spritebatch = new SpriteBatch(viewport);

		m_timer = new Timer();
		
		// Temp
		m_backTexture = new Texture2D("Background.tga");
		m_background = new Sprite(m_backTexture);
		m_background->setSize(Vector2(1000000,1000000));
		m_background->setPosition(Vector2(ContextWidht,ContextHeight));


		m_texture = new Texture2D("SciotoLogo.tga");
		m_texture2 = new Texture2D("Test.tga");
		for (int i=0; i<50;i++)
		{
			if (i%2)
				m_sprites.push_back(new Object(new Sprite(m_texture),Vector2((rand()%801-400),(rand()%801-400))));
			else
				m_sprites.push_back(new Object(new Sprite(m_texture2),Vector2((rand()%801-400),(rand()%801-400))));
			m_sprites[i]->setPosition(Vector2((rand()%1600),(rand()%1600)));
		}

		m_trotation = 0;
		m_texture3 = new Texture2D("trex.tga");
		m_trex = new Object(new Sprite(m_texture3),Vector2(-1000, -800));
		m_trex->setPosition(Vector2(1500,1500));

		a = Vector2(20,20);
		b = Vector2(500,-500);
		c = Vector2(0,800);
		d = Vector2(-800,200);
		r = Rectangle(m_trex->getPosition(),m_trex->m_sprite->m_size);
	}
	Engine::~Engine()
	{
	}

	void Engine::Update()
	{
		checkGlError("update");
		double deltaTime = m_timer->GetDeltaTime();
		LOGI("%.5f	%.5f",deltaTime, m_timer->GetCurTime());


		m_trotation += 0.1;
		m_spritebatch->Draw(m_background);

		
		LOGI("-	%.5f", m_timer->GetCurTime() - m_timer->GetMemTime());

		for (int i=0; i<m_sprites.size(); i++)
		{
			m_sprites[i]->update(deltaTime);
			if (m_sprites[i]->getPosition().x < 0)
			{
				m_sprites[i]->m_speed.x = -m_sprites[i]->m_speed.x;
				m_sprites[i]->update(deltaTime);
				m_sprites[i]->update(deltaTime);
			}

			m_spritebatch->Draw(m_sprites[i]->m_sprite);
		}
		
		LOGI("-	%.5f", m_timer->GetCurTime() - m_timer->GetMemTime());

		m_trex->update(deltaTime);
		m_trex->m_speed+=Vector2((rand()%101-50)*deltaTime/100.0f,(rand()%101-50)*deltaTime/100.0f);
		if (m_trotation < 0.5)
			m_trex->m_sprite->setRotation(m_trotation);
		else if (m_trotation < 1.5)
			m_trex->m_sprite->setRotation(1-m_trotation);
		else
			m_trotation = -0.5;
		
		LOGI("-	%.5f", m_timer->GetCurTime() - m_timer->GetMemTime());

		r = Rectangle(m_trex->getPosition()-m_trex->m_sprite->m_size/2.0f,m_trex->m_sprite->m_size);
		m_spritebatch->Draw(&r);
		m_spritebatch->Draw(m_trex->m_sprite);
		
		a = m_sprites[0]->m_sprite->getPosition();
		b = m_trex->m_sprite->getPosition();
		m_spritebatch->Draw(&a,Vector2(),0.0f,Vector4(0.0f,0.5f,0.6f,0.9f));
		m_spritebatch->Draw(&(b-a),a,0.0f,Vector4(0.0f,1.0f,0.0f,0.8f));
		//m_spritebatch->Draw(&c,a+b);
		//m_spritebatch->Draw(&d,a+b+c);

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
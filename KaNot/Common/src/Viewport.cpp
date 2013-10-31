#include "Viewport.h"
#include "OpenGL.h"

namespace Scioto
{

	float Viewport::m_scale, Viewport::m_blackbarH, Viewport::m_blackbarV;

	Viewport::Viewport(float desiredWidth,float desiredHeight,float width,float height)
	{
		FixAspectRatio(desiredWidth, desiredHeight, width, height);
	}

	Viewport::~Viewport()
	{}

	void Viewport::FixAspectRatio(float desiredWidth,float desiredHeight,float width,float height)
	{
		//Calculate desired Aspect Ratio
		float dAR =  desiredWidth/ desiredHeight;

		//Calculate real Aspect Ratio
		float rAR = width/height;
		float w,h;
		//Check Aspect Ratio's
		if(dAR==rAR)
		{
			//Same aspect, no letterboxing needed!
			m_scale = width/desiredWidth;
		}
		else if(dAR<rAR)
		{
			//Horizontal letterboxing needed!
			m_scale = height/desiredHeight;
			m_blackbarH = (width-m_scale*desiredWidth)/2;
		
		}
		else
		{
			//Vertical letterboxing needed!
			m_scale = width/desiredWidth;
			m_blackbarV = (height-(m_scale*desiredHeight))/2;
		}
		 w = desiredWidth*m_scale;
		 h = desiredHeight*m_scale;

		glViewport((int)m_blackbarH, (int)m_blackbarV,(int)w,(int)h); // Sets up the OpenGL viewport
	}
}
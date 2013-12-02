#pragma once
#ifndef VIEWPORT_H_SCIOTO
#define VIEWPORT_H_SCIOTO

#include <Sciotomath\Matrix4.h>

namespace Scioto
{
	class Viewport
	{
	public:
		Viewport(float desiredWidth,float desiredHeight,float width,float height);
		~Viewport();

		void setProjection(const Matrix4 projection);

		Matrix4 m_projection;

	private:
		float m_scale;
		float m_blackbarH, m_blackbarV;
		float m_dWidth, m_dHeight;
		float m_width, m_height;

		void FixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);
	};
}

#endif
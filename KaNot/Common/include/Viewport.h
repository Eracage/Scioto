#pragma once
#ifndef VIEWPORT_H
#define	VIEWPORT_H

namespace Scioto
{
	class Viewport
	{
	public:
		Viewport(float desiredWidth,float desiredHeight,float width,float height);
		~Viewport();

		void setProjection(const float projectionMatrix[16]);

		float m_projection[16];

	private:
		static float m_scale, m_blackbarH, m_blackbarV;

		void FixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);
	};
}

#endif
#ifndef VIEWPORT_H
#define	VIEWPORT_H

namespace Scioto
{
	class Viewport
	{
	public:
		Viewport(float desiredWidth,float desiredHeight,float width,float height);
		~Viewport();

		void FixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);

		static float m_scale, m_blackbarH, m_blackbarV;
	};
}

#endif
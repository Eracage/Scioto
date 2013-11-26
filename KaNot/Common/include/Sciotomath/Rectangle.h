#pragma once
#ifndef RECTANGLE_H_SCIOTO
#define RECTANGLE_H_SCIOTO

#include "Sciotomath/Vector2.h"

namespace Scioto
{
	class Rectangle
	{
	public:

		Rectangle();
		Rectangle(float Left, float Top, float Width, float Height);
		Rectangle(Vector2 Position, float Width, float Height);
		Rectangle(Vector2 Position, Vector2 Size);

		bool intersects(Rectangle rectangle);
		bool contains(Vector2 Position);

		~Rectangle();
		float width, height, left, top;

	private:

	};
}
#endif
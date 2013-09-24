#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <Sciotomath/Vector2.h>

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
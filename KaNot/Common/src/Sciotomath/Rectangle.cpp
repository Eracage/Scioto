#include <cmath>
#include <Sciotomath/Math.h>

namespace Scioto
{
	Rectangle::Rectangle()
		{
			left = 0;
			top = 0;
			width = 0;
			height = 0;
		}
		Rectangle::Rectangle(float Left, float Top, float Width, float Height)
		{
			left = Left;
			top = Top;
			width = Width;
			height = Height;
		}
		Rectangle::Rectangle(Vector2 Position, float Width, float Height)
		{
			left = Position.x;
			top = Position.y;
			width = Width;
			height = Height;
		}
		Rectangle::Rectangle(Vector2 Position, Vector2 Size)
		{
			left = Position.x;
			top = Position.y;
			width = Size.x;
			height = Size.y;
		}
		
		Rectangle::~Rectangle()
		{}
}
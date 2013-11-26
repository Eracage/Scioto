#include <cmath>
#include <Sciotomath/Math.h>

namespace Scioto
{
	Vector2::Vector2()
			: x(0), y(0)
	{}
	Vector2::Vector2(float X, float Y)
		: x(X), y(Y)
	{}
	Vector2::~Vector2(){}

	float Vector2::getLenght()
	{	
		return sqrt(pow(x,2) + pow(y,2));
	}
	float Vector2::getAngle()
	{
		if (x == 0)
		{
			if (y > 0)
				return 90;
			return 270;
		}
		else
		{
			float angle = float(atan(y/x)*(180.0f/PI));

			if (x < 0)
				angle += 180;

			else if (angle < 0)
				angle += 360;

			return angle;
		}
	}

	Vector2 operator -(const Vector2& RightVal)
	{
		return Vector2(-RightVal.x, -RightVal.y);
	}

	Vector2 operator +(const Vector2& LeftVal,const Vector2& RightVal)
	{
		return Vector2(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y);
	}
	Vector2 operator -(const Vector2& LeftVal,const Vector2& RightVal)
	{
		return Vector2(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y);
	}

	Vector2& operator +=(Vector2& LeftVal,const Vector2& RightVal)
	{
		LeftVal.x += RightVal.x;
		LeftVal.y += RightVal.y;
		return LeftVal;
	}
	Vector2& operator -=(Vector2& LeftVal,const Vector2& RightVal)
	{
		LeftVal.x -= RightVal.x;
		LeftVal.y -= RightVal.y;
		return LeftVal;
	}

	Vector2 operator /(const Vector2& LeftVal, const float& RightVal)
	{
		return Vector2(LeftVal.x / RightVal,LeftVal.y / RightVal);
	}
	Vector2& operator /=(Vector2& LeftVal, const float& RightVal)
	{
		LeftVal.x /= RightVal;
		LeftVal.y /= RightVal;
		return LeftVal;
	}

	bool operator ==(const Vector2& LeftVal,const Vector2& RightVal)
	{
		if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
			return true;
		return false;
	}
	bool operator !=(const Vector2& LeftVal,const Vector2& RightVal)
	{
		return !(LeftVal==RightVal);
	}

	Vector2 operator *(const Vector2& LeftVal, const float& RightVal)
	{
		return Vector2(LeftVal.x * RightVal,LeftVal.y * RightVal);
	}
	Vector2 operator *(const float& LeftVal, const Vector2& RightVal)
	{
		return Vector2(LeftVal * RightVal.x,LeftVal * RightVal.y);
	}

	Vector2& operator *=(Vector2& LeftVal,const float& RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		return LeftVal;
	}
}
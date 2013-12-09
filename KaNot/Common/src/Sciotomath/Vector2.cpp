#include <cmath>
#include "Sciotomath/Math.h"

namespace Scioto
{
	Vector2::Vector2()
			: x(0), y(0)
	{}
	Vector2::Vector2(float X, float Y)
		: x(X), y(Y)
	{}
	Vector2::~Vector2(){}

	float Vector2::getLenght() const
	{	
		return sqrt(pow(x,2) + pow(y,2));
	}
	float Vector2::getRadians() const
	{
		return atan2(y,x);
	}
	float Vector2::getAngle() const
	{
		return getRadians()*180.0/PI;
	}

	void Vector2::transform(const Vector2 position)
	{
		x += position.x;
		y += position.y;
	}
	void Vector2::rotateDegrees(const float degrees)
	{
		rotate(degrees/180*PI);
	}
	void Vector2::rotate(const float radians)
	{
		if (radians == 0)
			return;

		const float cosA = cos(radians);
		const float sinA = sin(radians);
		const float oldX = x;
		x = oldX*cosA-y*sinA;
		y = oldX*sinA+y*cosA;
	}
	void Vector2::scale(const Vector2 scale)
	{
		x*=scale.x;
		y*=scale.y;
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

	const Vector2& operator +=(Vector2& LeftVal,const Vector2& RightVal)
	{
		LeftVal.x += RightVal.x;
		LeftVal.y += RightVal.y;
		return LeftVal;
	}
	const Vector2& operator -=(Vector2& LeftVal,const Vector2& RightVal)
	{
		LeftVal.x -= RightVal.x;
		LeftVal.y -= RightVal.y;
		return LeftVal;
	}

	Vector2 operator /(const Vector2& LeftVal, const float& RightVal)
	{
		return Vector2(LeftVal.x / RightVal,LeftVal.y / RightVal);
	}
	const Vector2& operator /=(Vector2& LeftVal, const float& RightVal)
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

	const Vector2& operator *=(Vector2& LeftVal,const float& RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		return LeftVal;
	}
}
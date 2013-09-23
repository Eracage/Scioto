#include "Sciotomath/Math.h"
#define PI 3.14159265358979323846264
#include <cmath>

namespace Scioto
{

	Vector::Vector()
			: x(0), y(0)
	{}
	Vector::Vector(float X, float Y)
		: x(X), y(Y)
	{}
	Vector::~Vector(){}

	float Vector::getLenght()
	{	
		return sqrt(pow(x,2) + pow(y,2));
	}
	float Vector::getAngle()
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

	Vector Vector::operator-()
	{
		return Vector(-this->x, -this->y);
	}

	Vector Vector::operator +(const Vector& RightVal)
	{
		return Vector(this->x+RightVal.x,this->y+RightVal.y);
	}

	Vector Vector::operator -(const Vector& RightVal)
	{
		return Vector(this->x-RightVal.x,this->y-RightVal.y);
	}

	Vector &Vector::operator +=(const Vector& RightVal)
	{
		this->x += RightVal.x;
		this->y += RightVal.y;
		return *this;
	}

	Vector &Vector::operator -=(const Vector& RightVal)
	{
		this->x -= RightVal.x;
		this->y -= RightVal.y;
		return *this;
	}

	Vector Vector::operator /(float RightVal)
	{
		return Vector(this->x / (float)RightVal,this->y / (float)RightVal);
	}

	Vector &Vector::operator /=(float RightVal)
	{
		this->x /= (float)RightVal;
		this->y /= (float)RightVal;
		return *this;
	}

	bool Vector::operator ==(const Vector& RightVal)
	{
		if (this->x == RightVal.x && this->y == RightVal.y)
			return true;
		return false;
	}

	bool Vector::operator !=(const Vector& RightVal)
	{
		if (this->x == RightVal.x && this->y == RightVal.y)
			return false;
		return true;
	}


	Vector operator *(const Vector& LeftVal, const float RightVal)
	{
		return Vector(LeftVal.x * RightVal,LeftVal.y * RightVal);
	}

	Vector operator *(const float LeftVal, const Vector& RightVal)
	{
		return Vector(LeftVal * RightVal.x,LeftVal * RightVal.y);
	}

	const Vector &operator *=(Vector& LeftVal, float RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		return LeftVal;
	}
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
	Rectangle::Rectangle(Vector Position, float Width, float Height)
	{
		left = Position.x;
		top = Position.y;
		width = Width;
		height = Height;
	}
	Rectangle::Rectangle(Vector Position, Vector Size)
	{
		left = Position.x;
		top = Position.y;
		width = Size.x;
		height = Size.y;
	}
		
	Rectangle::~Rectangle()
	{}
}








//
//
//#include <EGEMath\Vector.h>
//#include <cmath>
//#include <SFML\Graphics\Transform.hpp>
//#define PI 3.14159265358979323846264
//
//namespace EGEMath
//{
//
//Vector::Vector()
//	: x(0), y(0)
//{}
//Vector::Vector(sf::Vector2f sfVector)
//{
//	x = sfVector.x;
//	y = sfVector.y;
//}
//Vector::Vector(sf::Vector2i sfVector)
//{
//	x = (float)sfVector.x;
//	y = (float)sfVector.y;
//}
//Vector::Vector(sf::Vector2u sfVector)
//{
//	x = (float)sfVector.x;
//	y = (float)sfVector.y;
//}
//Vector::Vector(float X, float Y)
//	: x(X), y(Y)
//{}
//Vector::~Vector(){}
//float Vector::getLenght()
//{
//	return sqrt(pow(x,2) + pow(y,2));
//}
//float Vector::getAngle()
//{
//	if (x == 0)
//	{
//		if (y > 0)
//			return 90;
//		return 270;
//	}
//	else
//	{
//		float angle = float(atan(y/x)*(180.0f/PI));
//		if (x < 0)
//			angle += 180;
//		else if (angle < 0)
//			angle += 360;
//		return angle;
//	}
//}
//Vector Vector::Normalize()
//{
//	float lenght = this->getLenght();
//	if (this->x != 0)
//		this->x /= lenght;
//	if (this->y != 0)
//		this->y /= lenght;
//	return Vector(*this);
//}
//void Vector::rotate(float Degrees)
//{
//	Degrees = fmod(Degrees,360);
//	sf::Transform transform;
//	transform.rotate(Degrees);
//	Vector rotated = transform.transformPoint(x,y);
//	x = rotated.x;
//	y = rotated.y;
//}
//#pragma region operators
//
//Vector operator -(const Vector& RightVal)
//{
//	return Vector(-RightVal.x, -RightVal.y);
//}
//
//Vector operator +(const Vector& LeftVal,const Vector& RightVal)
//{
//	return Vector(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y);
//}
//Vector operator -(const Vector& LeftVal,const Vector& RightVal)
//{
//	return Vector(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y);
//}
//
//Vector operator +=(Vector& LeftVal,const Vector& RightVal)
//{
//	LeftVal.x += RightVal.x;
//	LeftVal.y += RightVal.y;
//	return Vector(LeftVal.x,LeftVal.y);
//}
//Vector operator -=(Vector& LeftVal,const Vector& RightVal)
//{
//	LeftVal.x -= RightVal.x;
//	LeftVal.y -= RightVal.y;
//	return Vector(LeftVal.x,LeftVal.y);
//}
//
//Vector operator /(const Vector& LeftVal, const float& RightVal)
//{
//	return Vector(LeftVal.x / (float)RightVal,LeftVal.y / (float)RightVal);
//}
//Vector operator /=(Vector& LeftVal, const float& RightVal)
//{
//	LeftVal.x /= (float)RightVal;
//	LeftVal.y /= (float)RightVal;
//	return Vector(LeftVal.x,LeftVal.y);;
//}
//
//bool operator ==(const Vector& LeftVal,const Vector& RightVal)
//{
//	if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
//		return true;
//	return false;
//}
//bool operator !=(const Vector& LeftVal,const Vector& RightVal)
//{
//	if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
//		return false;
//	return true;
//}
//
//Vector operator *(const Vector& LeftVal, const float& RightVal)
//{
//	return Vector(LeftVal.x * RightVal,LeftVal.y * RightVal);
//}
//Vector operator *(const float& LeftVal, const Vector& RightVal)
//{
//	return Vector(LeftVal * RightVal.x,LeftVal * RightVal.y);
//}
//
//const Vector operator *=(Vector& LeftVal,const float& RightVal)
//{
//	LeftVal.x *= RightVal;
//	LeftVal.y *= RightVal;
//	return Vector(LeftVal.x,LeftVal.y);;
//}
//
//std::ostream& operator <<(std::ostream& Ostr, const Vector& RightVal)
//{
//    Ostr << "(";
//	Ostr << RightVal.x;
//	Ostr << ",";
//	Ostr << RightVal.y;
//	Ostr << ")";
//	return Ostr;
//}
//
//}
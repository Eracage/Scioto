#pragma once
#ifndef VECTOR2_H_SCIOTO
#define VECTOR2_H_SCIOTO

namespace Scioto
{
	class Vector2
		{
		public:
			Vector2();
			Vector2(float X, float Y);
			~Vector2();

			float getLenght();
			float getAngle();

			float x,y;


		private:

		};

	Vector2 operator -(const Vector2& RightVal);

	Vector2 operator +(const Vector2& LeftVal,const Vector2& RightVal);
	Vector2 operator -(const Vector2& LeftVal,const Vector2& RightVal);

	const Vector2& operator +=(Vector2& LeftVal,const Vector2& RightVal);
	const Vector2& operator -=(Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator /(const Vector2& LeftVal,const float& RightVal);
	const Vector2& operator /=(Vector2& LeftVal,const float& RightVal);

	bool operator ==(const Vector2& LeftVal,const Vector2& RightVal);
	bool operator !=(const Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator *(const Vector2& LeftVal, const float& RightVal);
	Vector2 operator *(const float& LeftVal, const Vector2& RightVal);

	const Vector2& operator *=(Vector2& LeftVal, const float& RightVal);
		/*std::ostream& operator <<(std::ostream& Ostr, const Vector& RightVal);*/
}
#endif
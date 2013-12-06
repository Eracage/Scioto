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

			float getLenght() const;
			/*
			Returns the angle of the vector in radians ranging from -PI to PI
			*/
			float getRadians() const;
			/*
			Returns the angle of the vector in degrees ranging from -180 to 180
			*/
			float getAngle() const;

			/*
			Transforms the current vector by given position vector.
			*/
			void transform(const Vector2 position);
			/*
			Rotates the current vector by given amount of degrees.
			*/
			void rotateDegrees(const float degrees);
			/*
			Rotates the current vector by given amount of radians.
			*/
			void rotate(const float radians);
			/*
			Scales the current vector by given scale vector.
			*/
			void scale(const Vector2 scale);

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
#ifndef VECTOR4_H
#define VECTOR4_H

namespace Scioto

{
	class Vector4
		{
		public:
			Vector4();
			Vector4(float X, float Y, float Z, float W);
			~Vector4();

			float getLenght();
			//float getAngle();

			float x,y,z,w;


		private:

		};

	Vector4 operator -(const Vector4& RightVal);

	Vector4 operator +(const Vector4& LeftVal,const Vector4& RightVal);
	Vector4 operator -(const Vector4& LeftVal,const Vector4& RightVal);

	Vector4& operator +=(Vector4& LeftVal,const Vector4& RightVal);
	Vector4& operator -=(Vector4& LeftVal,const Vector4& RightVal);

	Vector4 operator /(const Vector4& LeftVal,const float& RightVal);
	Vector4& operator /=(Vector4& LeftVal,const float& RightVal);

	bool operator ==(const Vector4& LeftVal,const Vector4& RightVal);
	bool operator !=(const Vector4& LeftVal,const Vector4& RightVal);

	Vector4 operator *(const Vector4& LeftVal, const float& RightVal);
	Vector4 operator *(const float& LeftVal, const Vector4& RightVal);

	Vector4& operator *=(Vector4& LeftVal, const float& RightVal);
}
#endif
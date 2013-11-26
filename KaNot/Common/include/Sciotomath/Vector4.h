#pragma once
#ifndef VECTOR4_H_SCIOTO
#define VECTOR4_H_SCIOTO

#include <Sciotomath\Vector3.h>

namespace Scioto
{
	class Vector4
	{
	public:
		Vector4();
		Vector4(const Vector3 Vec3, const float W);
		Vector4(const float X, const float Y, const float Z, const float W);
		~Vector4();

		float getLenght();
		//float getAngle();

		float x,y,z,w;

		const float& operator [](const unsigned int& index) const;
		float& operator [](const unsigned int& index);
	private:
	};
	

	Vector4 operator -(const Vector4& RightVal);

	Vector4 operator +(const Vector4& LeftVal,const Vector4& RightVal);
	Vector4 operator -(const Vector4& LeftVal,const Vector4& RightVal);

	const Vector4& operator +=(Vector4& LeftVal,const Vector4& RightVal);
	const Vector4& operator -=(Vector4& LeftVal,const Vector4& RightVal);

	Vector4 operator /(const Vector4& LeftVal,const float& RightVal);
	const Vector4& operator /=(Vector4& LeftVal,const float& RightVal);

	bool operator ==(const Vector4& LeftVal,const Vector4& RightVal);
	bool operator !=(const Vector4& LeftVal,const Vector4& RightVal);

	Vector4 operator *(const Vector4& LeftVal, const float& RightVal);
	Vector4 operator *(const float& LeftVal, const Vector4& RightVal);

	const Vector4& operator *=(Vector4& LeftVal, const float& RightVal);

}
#endif
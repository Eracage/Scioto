#pragma once
#ifndef VECTOR3_H_SCIOTO
#define VECTOR3_H_SCIOTO

namespace Scioto
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float X, float Y, float Z);
		~Vector3();

		float getLenght();
		//float getAngle();

		float x,y,z;
			
		const float& operator [](const unsigned int& index) const;
		float& operator [](const unsigned int& index);
	private:

	};

	Vector3 operator -(const Vector3& RightVal);

	Vector3 operator +(const Vector3& LeftVal,const Vector3& RightVal);
	Vector3 operator -(const Vector3& LeftVal,const Vector3& RightVal);

	const Vector3& operator +=(Vector3& LeftVal,const Vector3& RightVal);
	const Vector3& operator -=(Vector3& LeftVal,const Vector3& RightVal);

	Vector3 operator /(const Vector3& LeftVal,const float& RightVal);
	const Vector3& operator /=(Vector3& LeftVal,const float& RightVal);

	bool operator ==(const Vector3& LeftVal,const Vector3& RightVal);
	bool operator !=(const Vector3& LeftVal,const Vector3& RightVal);

	Vector3 operator *(const Vector3& LeftVal, const float& RightVal);
	Vector3 operator *(const float& LeftVal, const Vector3& RightVal);

	const Vector3& operator *=(Vector3& LeftVal, const float& RightVal);
}
#endif
#pragma once
#ifndef MATRIX4_H_SCIOTO
#define MATRIX4_H_SCIOTO

#include <Sciotomath\Vector4.h>
#include <Sciotomath\Matrix3.h>

namespace Scioto
{
	class Matrix4
	{
	public:
		/**
		Creates Identity Matrix
		*/
		Matrix4();
		Matrix4(const float* FirstElement);
		Matrix4(const Matrix3 mat3);
		Matrix4(
			const Vector4& Row1,
			const Vector4& Row2,
			const Vector4& Row3,
			const Vector4& Row4);
		Matrix4(
			const float& r1s1,const float& r1s2,const float& r1s3,const float& r1s4,
			const float& r2s1,const float& r2s2,const float& r2s3,const float& r2s4,
			const float& r3s1,const float& r3s2,const float& r3s3,const float& r3s4,
			const float& r4s1,const float& r4s2,const float& r4s3,const float& r4s4);
		~Matrix4();

		float* FirstElement();

		const Vector4& operator [](const unsigned int& index) const;
		Vector4& operator [](const unsigned int& index);

	private:
		Vector4 r1,r2,r3,r4;

	};
	
	Matrix4 operator *(const Matrix4& LeftVal, const Matrix4& RightVal);
	const Matrix4 operator *=(Matrix4& LeftVal, const Matrix4& RightVal);

	Vector4 operator *(const Vector4& LeftVal, const Matrix4& RightVal);
	const Vector4 operator *=(Vector4& LeftVal, const Matrix4& RightVal);
	
}

#endif
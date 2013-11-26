#pragma once
#ifndef MATRIX3_H_SCIOTO
#define MATRIX3_H_SCIOTO

#include <Sciotomath\Vector3.h>

namespace Scioto
{
	class Matrix3
	{
	public:
		/**
		Creates Identity Matrix
		*/
		Matrix3();
		Matrix3(
			const Vector3& Column1,
			const Vector3& Column2,
			const Vector3& Column3);
		Matrix3(
			const float& c1r1,const float& c1r2,const float& c1r3,
			const float& c2r1,const float& c2r2,const float& c2r3,
			const float& c3r1,const float& c3r2,const float& c3r3);
		~Matrix3();

		float* GetElements();

		const Vector3& operator [](const unsigned int& index) const;
		Vector3& operator [](const unsigned int& index);

	private:
		Vector3 c1,c2,c3;

	};

	Matrix3 operator *(const Matrix3& LeftVal, const Matrix3& RightVal);
	const Matrix3 operator *=(Matrix3& LeftVal, const Matrix3& RightVal);
	
}

#endif
#include <Sciotomath\Matrix3.h>
#include <Sciotomath\Math.h>

namespace Scioto
{
	Matrix3::Matrix3()
		:
		c1(Vector3(1.f,0.f,0.f)),
		c2(Vector3(0.f,1.f,0.f)),
		c3(Vector3(0.f,0.f,1.f))
	{}
	Matrix3::Matrix3(const float* fe)
		:
		c1(fe[0],fe[1],fe[2]),
		c2(fe[3],fe[4],fe[5]),
		c3(fe[6],fe[7],fe[8])
	{}
	Matrix3::Matrix3(
		const Vector3& Column1,
		const Vector3& Column2,
		const Vector3& Column3)
		: 
		c1(Column1),
		c2(Column2),
		c3(Column3)
	{}
	Matrix3::Matrix3(
		const float& c1r1,const float& c1r2,const float& c1r3,
		const float& c2r1,const float& c2r2,const float& c2r3,
		const float& c3r1,const float& c3r2,const float& c3r3)
		:
		c1(c1r1,c1r2,c1r3),
		c2(c2r1,c2r2,c2r3),
		c3(c3r1,c3r2,c3r3)
	{}
	Matrix3::~Matrix3()
	{}
	
	float* Matrix3::FirstElement()
	{
		return &c1.x;
	}
	
	const Vector3& Matrix3::operator [](const unsigned int& index) const
	{
		return (&c1)[index];
	}
	Vector3& Matrix3::operator [](const unsigned int& index)
	{
		return (&c1)[index];
	}
	
	Matrix3 operator *(const Matrix3& L, const Matrix3& R)
	{
		return Matrix3(
			L[0][0] * R[0][0] + L[1][0] * R[0][1] + L[2][0] * R[0][2],
			L[0][1] * R[0][0] + L[1][1] * R[0][1] + L[2][1] * R[0][2],
			L[0][2] * R[0][0] + L[1][2] * R[0][1] + L[2][2] * R[0][2],
			L[0][0] * R[1][0] + L[1][0] * R[1][1] + L[2][0] * R[1][2],
			L[0][1] * R[1][0] + L[1][1] * R[1][1] + L[2][1] * R[1][2],
			L[0][2] * R[1][0] + L[1][2] * R[1][1] + L[2][2] * R[1][2],
			L[0][0] * R[2][0] + L[1][0] * R[2][1] + L[2][0] * R[2][2],
			L[0][1] * R[2][0] + L[1][1] * R[2][1] + L[2][1] * R[2][2],
			L[0][2] * R[2][0] + L[1][2] * R[2][1] + L[2][2] * R[2][2]
			);
	}
	const Matrix3 operator *=(Matrix3& LeftVal, const Matrix3& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}

}
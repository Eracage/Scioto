#include <Sciotomath\Matrix4.h>
#include <Sciotomath\Math.h>

namespace Scioto
{
	Matrix4::Matrix4()
		:
		c1(Vector4(1,0,0,0)),
		c2(Vector4(0,1,0,0)),
		c3(Vector4(0,0,1,0)),
		c4(Vector4(0,0,0,1))
	{}
	Matrix4::Matrix4(
		const Vector4& Column1,
		const Vector4& Column2,
		const Vector4& Column3,
		const Vector4& Column4)
		: 
		c1(Column1),
		c2(Column2),
		c3(Column3),
		c4(Column4)
	{}
	Matrix4::Matrix4(
		const float& c1r1,const float& c1r2,const float& c1r3,const float& c1r4,
		const float& c2r1,const float& c2r2,const float& c2r3,const float& c2r4,
		const float& c3r1,const float& c3r2,const float& c3r3,const float& c3r4,
		const float& c4r1,const float& c4r2,const float& c4r3,const float& c4r4)
		:
		c1(c1r1,c1r2,c1r3,c1r4),
		c2(c2r1,c2r2,c2r3,c2r4),
		c3(c3r1,c3r2,c3r3,c3r4),
		c4(c4r1,c4r2,c4r3,c4r4)
	{}
	Matrix4::~Matrix4()
	{}
	
	float* Matrix4::GetElements()
	{
		return &c1.x;
	}
	
	const Vector4& Matrix4::operator [](const unsigned int& index) const
	{
		return (&c1)[index];
	}
	Vector4& Matrix4::operator [](const unsigned int& index)
	{
		return (&c1)[index];
	}
	
	Matrix4 operator *(const Matrix4& L, const Matrix4& R)
	{
		return Matrix4(
			L[0][0] * R[0][0] + L[1][0] * R[0][1] + L[2][0] * R[0][2] + L[3][0] * R[0][3],
			L[0][1] * R[0][0] + L[1][1] * R[0][1] + L[2][1] * R[0][2] + L[3][1] * R[0][3],
			L[0][2] * R[0][0] + L[1][2] * R[0][1] + L[2][2] * R[0][2] + L[3][2] * R[0][3],
			L[0][3] * R[0][0] + L[1][3] * R[0][1] + L[2][3] * R[0][2] + L[3][3] * R[0][3],
			L[0][0] * R[1][0] + L[1][0] * R[1][1] + L[2][0] * R[1][2] + L[3][0] * R[1][3],
			L[0][1] * R[1][0] + L[1][1] * R[1][1] + L[2][1] * R[1][2] + L[3][1] * R[1][3],
			L[0][2] * R[1][0] + L[1][2] * R[1][1] + L[2][2] * R[1][2] + L[3][2] * R[1][3],
			L[0][3] * R[1][0] + L[1][3] * R[1][1] + L[2][3] * R[1][2] + L[3][3] * R[1][3],
			L[0][0] * R[2][0] + L[1][0] * R[2][1] + L[2][0] * R[2][2] + L[3][0] * R[2][3],
			L[0][1] * R[2][0] + L[1][1] * R[2][1] + L[2][1] * R[2][2] + L[3][1] * R[2][3],
			L[0][2] * R[2][0] + L[1][2] * R[2][1] + L[2][2] * R[2][2] + L[3][2] * R[2][3],
			L[0][3] * R[2][0] + L[1][3] * R[2][1] + L[2][3] * R[2][2] + L[3][3] * R[2][3],
			L[0][0] * R[3][0] + L[1][0] * R[3][1] + L[2][0] * R[3][2] + L[3][0] * R[3][3],
			L[0][1] * R[3][0] + L[1][1] * R[3][1] + L[2][1] * R[3][2] + L[3][1] * R[3][3],
			L[0][2] * R[3][0] + L[1][2] * R[3][1] + L[2][2] * R[3][2] + L[3][2] * R[3][3],
			L[0][3] * R[3][0] + L[1][3] * R[3][1] + L[2][3] * R[3][2] + L[3][3] * R[3][3]
			);
	}
	const Matrix4 operator *=(Matrix4& LeftVal, const Matrix4& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}

}
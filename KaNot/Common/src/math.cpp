#include "Sciotomath/Math.h"
#define PI 3.14159265358979323846264
#include <cmath>

namespace Scioto
{

	vector::vector()
			: x(0), y(0)
	{}
	vector::vector(float X, float Y)
		: x(X), y(Y)
	{}
	vector::~vector(){}

	float vector::getLenght()
		{	
			return sqrt(pow(x,2) + pow(y,2));
		}
	float vector::getAngle()
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

	vector vector::operator-()
		{
			return vector(-this->x, -this->y);
		}

		vector vector::operator +(const vector& RightVal)
		{
			return vector(this->x+RightVal.x,this->y+RightVal.y);
		}

		vector vector::operator -(const vector& RightVal)
		{
			return vector(this->x-RightVal.x,this->y-RightVal.y);
		}

		vector &vector::operator +=(const vector& RightVal)
		{
			this->x += RightVal.x;
			this->y += RightVal.y;
			return *this;
		}

		vector &vector::operator -=(const vector& RightVal)
		{
			this->x -= RightVal.x;
			this->y -= RightVal.y;
			return *this;
		}

		vector vector::operator /(float RightVal)
		{
			return vector(this->x / (float)RightVal,this->y / (float)RightVal);
		}

		vector &vector::operator /=(float RightVal)
		{
			this->x /= (float)RightVal;
			this->y /= (float)RightVal;
			return *this;
		}

		bool vector::operator ==(const vector& RightVal)
		{
			if (this->x == RightVal.x && this->y == RightVal.y)
				return true;
			return false;
		}

		bool vector::operator !=(const vector& RightVal)
		{
			if (this->x == RightVal.x && this->y == RightVal.y)
				return false;
			return true;
		}


		vector operator *(const vector& LeftVal, const float RightVal)
		{
			return vector(LeftVal.x * RightVal,LeftVal.y * RightVal);
		}

		vector operator *(const float LeftVal, const vector& RightVal)
		{
			return vector(LeftVal * RightVal.x,LeftVal * RightVal.y);
		}

		const vector &operator *=(vector& LeftVal, float RightVal)
		{
			LeftVal.x *= RightVal;
			LeftVal.y *= RightVal;
			return LeftVal;
		}
			rectangle::rectangle()
		{
			left = 0;
			top = 0;
			width = 0;
			height = 0;
		}
		rectangle::rectangle(float Left, float Top, float Width, float Height)
		{
			left = Left;
			top = Top;
			width = Width;
			height = Height;
		}
		rectangle::rectangle(vector Position, float Width, float Height)
		{
			left = Position.x;
			top = Position.y;
			width = Width;
			height = Height;
		}
		rectangle::rectangle(vector Position, vector Size)
		{
			left = Position.x;
			top = Position.y;
			width = Size.x;
			height = Size.y;
		}
		
		rectangle::~rectangle()
		{}
}
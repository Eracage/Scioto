#ifndef MATH_H
#define MATH_H

namespace Scioto
{


	class vector
	{
	public:
		vector();
		vector(float X, float Y);
		~vector();

	float getLenght();
	float getAngle();

	float x,y;

	vector operator -();

	vector operator +(const vector& RightVal);
	vector operator -(const vector& RightVal);

	vector &operator +=(const vector& RightVal);
	vector &operator -=(const vector& RightVal);

	vector operator /(float RightVal);
	vector &operator /=(float RightVal);

	bool operator ==(const vector& RightVal);
	bool operator !=(const vector& RightVal);

	friend vector operator *(const vector& LeftVal, const float RightVal);
	friend vector operator *(const float LeftVal, const vector& RightVal);

	friend const vector &operator *=(vector& LeftVal, const float RightVal);

	private:

	};


	class rectangle
	{
	public:
		rectangle();
		rectangle(float Left, float Top, float Width, float Height);
		rectangle(vector Position, float Width, float Height);
		rectangle(vector Position, vector Size);

		bool intersects(rectangle Rectangle);
		bool contains(vector Position);

		~rectangle();
		float width, height, left, top;

	private:

	};


}

#endif
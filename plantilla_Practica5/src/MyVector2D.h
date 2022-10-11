#pragma once

//#define PI=3.14f

#include <math.h>

class MyVec2D
{

public:
	float x;
	float y;

	//Constructores
	MyVec2D();
	MyVec2D(float _x);
	MyVec2D(float _x, float _y);
	//Constructor Copia
	MyVec2D(const MyVec2D& other);
	//Destructor
	~MyVec2D() {};

	MyVec2D AddScalar(const float _scalar);
	MyVec2D MyVec2D::Multiply(const float _scalar);
	MyVec2D MyVec2D::Multiply(const MyVec2D& other);



	MyVec2D AddVectors(const MyVec2D& other) const;
	MyVec2D AddVectors(const float _x, float _y) const;

	//void MyVec2D::MultiplyVectors(MyVec2D& other);


	float Magnitude();

	MyVec2D Normalize(MyVec2D other, MyVec2D& _VecNormalize_);

	void Normalize();
	//float DotProduct(MyVec2D& other);

	void rotatePoint(float _originX, float _originY, float _angle, MyVec2D& pos);
	

	float Distance(const MyVec2D& other) const;
	


	float ProductoEscalar(const MyVec2D& other);
	float Angle(const MyVec2D& other);
	
	MyVec2D operator+(const float _scalar)
	{
		return MyVec2D(x + _scalar, y + _scalar);
	}
	MyVec2D operator+(const MyVec2D& other)
	{
		return MyVec2D(x + other.x, y + other.y);
	}
	MyVec2D operator+=(const MyVec2D& other)
	{
		return MyVec2D(x + other.x, y + other.y);
	}
	MyVec2D operator*(const float _scalar)
	{
		return MyVec2D(x * _scalar, y * _scalar);
	}
	MyVec2D operator*(const MyVec2D& other)
	{
		return MyVec2D(x * other.x, y * other.y);
	}

	MyVec2D operator-(const MyVec2D& other)
	{
		return MyVec2D(x - other.x, y - other.y);
	}

};




float RadToDegree(float _angle);
float DegreeToRad(float _angle);




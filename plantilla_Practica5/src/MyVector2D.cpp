#include "MyVector2D.h"
#include <vector>
//Constructores

MyVec2D::MyVec2D()
{
	x = 0.f;
	y = 0.f;
}

MyVec2D::MyVec2D(float _x)
	: x(_x)
	, y(_x)
{
}


MyVec2D::MyVec2D(float _x, float _y)
	: x(_x)		//MyVec2D(_x)
	, y(_y)
{
}

//Constructor de copia
MyVec2D::MyVec2D(const MyVec2D& other)
	: x(other.x)
	, y(other.y)
{
}




MyVec2D MyVec2D::AddScalar(const float _scalar) 
{
	return MyVec2D(x + _scalar, y + _scalar);
}

MyVec2D MyVec2D::Multiply(const float _scalar) 
{
	return MyVec2D(x * _scalar, y * _scalar);
}

MyVec2D MyVec2D::Multiply(const MyVec2D& other)
{
	return MyVec2D(x * other.x, y * other.y);

}

MyVec2D MyVec2D::AddVectors(const MyVec2D& other) const
{
	return MyVec2D(x + other.x, y + other.y);
}

MyVec2D MyVec2D::AddVectors(float _x, float _y) const
{
	return MyVec2D(x + _x, y + _y);
}

//void MyVec2D::MultiplyVectors(MyVec2D& other)
//{
//	x = x * other.x;
//	y = y * other.y;
//}

float MyVec2D::Magnitude()
{
	return sqrtf((x * x) + (y * y));
}



MyVec2D MyVec2D::Normalize(MyVec2D other, MyVec2D& _VecNormalize_)
{
	float length = other.Magnitude();
	_VecNormalize_.x = (other.x / length);
	_VecNormalize_.y = (other.y / length);

	return _VecNormalize_;
}

void MyVec2D::Normalize()
{
	float length = Magnitude();
	x = (x / length);
	y = (y / length);
	
}

//float DotProduct(MyVec2D other, MyVec2D other2)
//{
//	other.Normalize();
//	other2.Normalize();
//	return 1; // (other * other2 * cosf());
//}

void rotatePoint(float _originX, float _originY, float _angle, MyVec2D& pos)
{
	//Translate point back to origin
	pos.x -= _originX;
	pos.y -= _originY;

	//Rotate Point
	float xNew = pos.x * cosf(_angle) - pos.y * sinf(_angle);
	float yNew = pos.x * sinf(_angle) + pos.y * cosf(_angle);

	//translate point back
	pos.x = xNew + _originX;
	pos.y = yNew + _originY;

	//return pos;

}

float ProductoEscalar(const MyVec2D& other)
{
	return 0;
}


float MyVec2D::Distance(const MyVec2D& other) const
{
	MyVec2D auxVec(x, y);
	auxVec = auxVec - other;
	return auxVec.Magnitude();
}
float MyVec2D::Angle(const MyVec2D& other)
{
//
	float angle = atan2f(other.x - x, other.y - y);
	//float angle = atan2f(x-other.x, y- other.y);
	angle = RadToDegree(angle);
	if (angle < 0)
	{
		angle += 360;
	}
	return angle;
}


float RadToDegree(float _angle)
{
	return _angle * (180.f / 3.14f);
}

float DegreeToRad(float _angle)
{
	return _angle * (3.14f / 180.f);
}

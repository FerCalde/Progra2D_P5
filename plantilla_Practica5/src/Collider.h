#pragma once

#include "MyVector2D.h"
#include "glfw3.h"

class Collider
{
	Collider();
	
	virtual bool Collides(const Collider& other) const = 0;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const = 0;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const = 0;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const = 0;
};

class CircleCollider : public Collider
{
	public:
	CircleCollider(const MyVec2D& _circlePos, float _fCircleRadius);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};

class RectCollider : public Collider
{
	public:
	RectCollider(const MyVec2D& _rectPos, const MyVec2D& _rectSize);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};

class PixelsCollider : public Collider
{
	public:
	PixelsCollider(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};
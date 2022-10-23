#pragma once

#include "MyVector2D.h"
#include "glfw3.h"

class Collider
{
	
	
protected:
	Collider(const MyVec2D& _posCollider);
	//Collider(const);
	
	MyVec2D m_positionCollider;
	
	
public:
	
	virtual bool Collides(const Collider& other) const = 0;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const = 0;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const = 0;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const = 0;

	void SetPosition(const MyVec2D _pos);
	MyVec2D GetPosition() const;
protected:

	//Checkers Methods
	bool CheckCircleCircle(const MyVec2D& _pos1, float _fRadius1, const MyVec2D& _pos2, float _fRadius2) const;
	
	bool CheckCircleRect(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _rectPos, const MyVec2D& _rectSize) const;
	
	bool CheckCirclePixels(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const;
	
	bool CheckRectRect(const MyVec2D& _rectPos1, const MyVec2D& _rectSize1, const MyVec2D& _rectPos2, const MyVec2D& _rectSize2) const;
	
	bool CheckRectPixels(const MyVec2D& _rectPos, const MyVec2D& _rectSize, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const;
	
	bool CheckPixelsPixels(const MyVec2D& _pixelsPos1, const MyVec2D& _pixelSize1, const uint8_t* _pixels1, const MyVec2D& _pixelsPos2, const MyVec2D& _pixelSize2, const uint8_t* _pixels2) const;

	

};

class CircleCollider : public Collider
{
	float m_fCircleRadius = 0.0f;
	
	public:
	CircleCollider(const MyVec2D& _circlePos, float _fCircleRadius);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};

class RectCollider : public Collider
{
	MyVec2D m_RectSize{0};
	
	public:
	RectCollider(const MyVec2D& _rectPos, const MyVec2D& _rectSize);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};

class PixelsCollider : public Collider
{
	MyVec2D m_PixelSize{0};
	const uint8_t* m_Pixels = nullptr;

	public:
	PixelsCollider(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels);
	
	virtual bool Collides(const Collider& other) const override;
	
	virtual bool Collides(const MyVec2D& _circlePos, float _fCircleRadius) const override;
	
	virtual bool Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const override;

	virtual bool Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const override;
};
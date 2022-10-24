#include "Collider.h"

#pragma region COLLIDER_BASE

Collider::Collider(const MyVec2D& _posCollider)
	: m_positionCollider(_posCollider)
{
}

void Collider::SetPosition(const MyVec2D _pos)
{
	m_positionCollider = _pos;
}

MyVec2D Collider::GetPosition() const
{
	return m_positionCollider;
}

bool Collider::CheckCircleCircle(const MyVec2D& _pos1, float _fRadius1, const MyVec2D& _pos2, float _fRadius2) const
{
	//Distance Centers < Sum Radius
	float distCenters = _pos1.Distance(_pos2);
	float sumRadius = _fRadius1 + _fRadius2;
	//bool bCollisionDetected = distCenters < sumRadius ? true : false;
	return distCenters < sumRadius;
}

bool Collider::CheckCircleRect(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
	return false;
}

bool Collider::CheckCirclePixels(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	return false;
}

bool Collider::CheckRectRect(const MyVec2D& _rectPos1, const MyVec2D& _rectSize1, const MyVec2D& _rectPos2, const MyVec2D& _rectSize2) const
{
	//Limits Rect1
	float limitRightRect1 = _rectPos1.x + _rectSize1.x * 0.5f;
	float limitLeftRect1 = _rectPos1.x - _rectSize1.x * 0.5f;
	float limitTopRect1 = _rectPos1.y - _rectSize1.y * 0.5f;
	float limitBottomRect1 = _rectPos1.y + _rectSize1.y * 0.5f;
	//Limits Rect2
	float limitRightRect2 = _rectPos2.x + _rectSize2.x * 0.5f;
	float limitLeftRect2 = _rectPos2.x - _rectSize2.x * 0.5f;
	float limitTopRect2 = _rectPos2.y - _rectSize2.y * 0.5f;
	float limitBottomRect2 = _rectPos2.y + _rectSize2.y * 0.5f;


	//Check Rect2 inside Rect1

	bool bRect2RightLimitInside = (limitRightRect2 <= limitRightRect1) && (limitRightRect2 >= limitLeftRect1);
	bool bRect2LeftLimitInside = (limitLeftRect2 <= limitRightRect1) && (limitLeftRect2 >= limitLeftRect1);

	if (bRect2RightLimitInside || bRect2LeftLimitInside)
	{
		bool bRect2TopLimitInside = (limitTopRect2 >= limitTopRect1) && (limitTopRect2 <= limitBottomRect1);
		bool bRect2BottomLimitInside = (limitBottomRect2 >= limitTopRect1) && (limitBottomRect2 <= limitBottomRect1);

		if (bRect2TopLimitInside || bRect2BottomLimitInside)
		{
			return true;
		}
	}



	//Check Rect 1 inside Rect2
	bool bRect1RightLimitInside = (limitRightRect1 <= limitRightRect2) && (limitRightRect1 >= limitLeftRect2);
	bool bRect1LeftLimitInside = (limitLeftRect1 <= limitRightRect2) && (limitLeftRect1 >= limitLeftRect2);

	if (bRect1RightLimitInside || bRect1LeftLimitInside)
	{
		bool bRect1TopLimitInside = (limitTopRect1 >= limitTopRect2) && (limitTopRect1 <= limitBottomRect2);
		bool bRect1BottomLimitInside = (limitBottomRect1 >= limitTopRect2) && (limitBottomRect1 <= limitBottomRect2);

		bool bRect1YInsideRect2 = false;
		if (bRect1TopLimitInside || bRect1BottomLimitInside)
		{
			return true;
		}
	}


	//If there is not Collision (No Rect inside each other)
	return false;
}

bool Collider::CheckRectPixels(const MyVec2D& _rectPos, const MyVec2D& _rectSize, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	return false;
}

bool Collider::CheckPixelsPixels(const MyVec2D& _pixelsPos1, const MyVec2D& _pixelSize1, const uint8_t* _pixels1, const MyVec2D& _pixelsPos2, const MyVec2D& _pixelSize2, const uint8_t* _pixels2) const
{
	return false;
}


#pragma endregion COLLIDER_BASE

#pragma region COLLIDER_CIRCLE

CircleCollider::CircleCollider(const MyVec2D& _circlePos, float _fCircleRadius)
	: Collider(_circlePos),
	m_fCircleRadius(_fCircleRadius)
{

}

bool CircleCollider::Collides(const Collider& other) const
{
	return other.Collides(m_positionCollider, m_fCircleRadius);
}

bool CircleCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
	return CheckCircleCircle(m_positionCollider, m_fCircleRadius, _circlePos, _fCircleRadius);
}

bool CircleCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
	return CheckCircleRect(m_positionCollider, m_fCircleRadius, _rectPos, _rectSize);
}

bool CircleCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	return CheckCirclePixels(m_positionCollider, m_fCircleRadius, _pixelsPos, _pixelSize, _pixels);
}


#pragma endregion COLLIDER_CIRCLE

#pragma region COLLIDER_RECTANGLE

RectCollider::RectCollider(const MyVec2D& _rectPos, const MyVec2D& _rectSize)
	: Collider(_rectPos),
	m_RectSize(_rectSize)
{

}

bool RectCollider::Collides(const Collider& other) const
{
	return other.Collides(m_positionCollider, m_RectSize);
}

bool RectCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
	return CheckCircleRect(_circlePos, _fCircleRadius, m_positionCollider, m_RectSize);
}

bool RectCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
	return CheckRectRect(m_positionCollider, m_RectSize, _rectPos, _rectSize);
}

bool RectCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	return CheckRectPixels(m_positionCollider, m_RectSize, _pixelsPos, _pixelSize, _pixels);
}



#pragma endregion COLLIDER_RECTANGLE

#pragma region COLLIDER_PIXELS


PixelsCollider::PixelsCollider(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels)
	: Collider(_pixelsPos),
	m_PixelSize(_pixelSize),
	m_Pixels(_pixels)
{

}

bool PixelsCollider::Collides(const Collider& other) const
{
	return other.Collides(m_positionCollider, m_PixelSize);
}

bool PixelsCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
	return CheckCirclePixels(_circlePos, _fCircleRadius, m_positionCollider, m_PixelSize, m_Pixels);
}

bool PixelsCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
	return CheckRectPixels(_rectPos, _rectSize, m_positionCollider, m_PixelSize, m_Pixels);
}

bool PixelsCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	return CheckPixelsPixels(m_positionCollider, m_PixelSize, m_Pixels, _pixelsPos, _pixelSize, _pixels);
}

#pragma endregion COLLIDER_PIXELS


#include "Collider.h"

#pragma region COLLIDER_BASE

Collider::Collider(const MyVec2D& _posCollider)
    : m_positionCollider(_posCollider)
{
}

bool Collider::CheckCircleCircle(const MyVec2D& _pos1, float _fRadius1, const MyVec2D& _pos2, float _fRadius2) const
{
    return false;
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


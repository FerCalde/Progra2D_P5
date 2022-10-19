#include "Collider.h"

CircleCollider::CircleCollider(const MyVec2D& _circlePos, float _fCircleRadius)
    : Collider(_circlePos),
    m_fCircleRadius(_fCircleRadius)
{
	
}

bool CircleCollider::Collides(const Collider& other) const
{
    return false;
}

bool CircleCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
    return false;
}

bool CircleCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
    return false;
}

bool CircleCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
    return false;
}

RectCollider::RectCollider(const MyVec2D& _rectPos, const MyVec2D& _rectSize)
    : Collider(_rectPos),
    m_RectSize(_rectSize)
{
}

bool RectCollider::Collides(const Collider& other) const
{
    return false;
}

bool RectCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
    return false;
}

bool RectCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
    return false;
}

bool RectCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
    return false;
}

PixelsCollider::PixelsCollider(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels)
    : Collider(_pixelsPos),
    m_PixelSize(_pixelSize),
    m_Pixels(_pixels)
{
}

bool PixelsCollider::Collides(const Collider& other) const
{
    return false;
}

bool PixelsCollider::Collides(const MyVec2D& _circlePos, float _fCircleRadius) const
{
    return false;
}

bool PixelsCollider::Collides(const MyVec2D& _rectPos, const MyVec2D& _rectSize) const
{
    return false;
}

bool PixelsCollider::Collides(const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
    return false;
}

Collider::Collider(const MyVec2D& _posCollider)
    : m_positionCollider(_posCollider)
{
}

bool Collider::CheckCircleCircle(const MyVec2D& _pos1, float _fRadius1, const MyVec2D& _pos2, float _fRadius2)
{
    return false;
}

bool Collider::CheckCircleRect(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _rectPos, const MyVec2D& _rectSize)
{
    return false;
}

bool Collider::CheckCirclePixels(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels)
{
    return false;
}

bool Collider::CheckRectRect(const MyVec2D& _rectPos1, const MyVec2D& _rectSize1, const MyVec2D& _rectPos2, const MyVec2D& _rectSize2)
{
    return false;
}

bool Collider::CheckRectPixels(const MyVec2D& _rectPos, const MyVec2D& _rectSize, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels)
{
    return false;
}

bool Collider::CheckPixelsPixels(const MyVec2D& _pixelsPos1, const MyVec2D& _pixelSize1, const uint8_t* _pixels1, const MyVec2D& _pixelsPos2, const MyVec2D& _pixelSize2, const uint8_t* _pixels2)
{
    return false;
}

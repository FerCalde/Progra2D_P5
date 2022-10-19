#include "Collider.h"

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

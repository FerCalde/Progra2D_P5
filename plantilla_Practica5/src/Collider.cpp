#include "Collider.h"
#include <algorithm> //std::clamp is included in <algorithm> in C++17
#include <vector>

template <typename T>
T Clamp(const T& _value, const T& _lowerValue, const T& _upperValue) {
	return std::max(_lowerValue, std::min(_value, _upperValue));
}


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
	float limitRightRect = _rectPos.x + _rectSize.x * 0.5f;
	float limitLeftRect = _rectPos.x - _rectSize.x * 0.5f;
	float limitTopRect = _rectPos.y - _rectSize.y * 0.5f;
	float limitBottomRect = _rectPos.y + _rectSize.y * 0.5f;


	//Closest Point on Rect to Circle
	float closestX = Clamp(_circlePos.x, limitLeftRect, limitRightRect);
	float closestY = Clamp(_circlePos.y, limitTopRect, limitBottomRect);

	//Distance between Circle and Closest Point
	MyVec2D closestPoint{ closestX, closestY };
	if (closestPoint.Distance(_circlePos) <= _fCircleRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collider::CheckCirclePixels(const MyVec2D& _circlePos, float _fCircleRadius, const MyVec2D& _pixelsPos, const MyVec2D& _pixelSize, const uint8_t* _pixels) const
{
	if (!CheckCircleRect(_circlePos, _fCircleRadius, _pixelsPos, _pixelSize))
	{
		return false;
	}

	//Puntos de cortes
	float limitRightPixel = _pixelsPos.x + _pixelSize.x * 0.5f;
	float limitLeftPixel = _pixelsPos.x - _pixelSize.x * 0.5f;
	float limitTopPixel = _pixelsPos.y - _pixelSize.y * 0.5f;
	float limitBottomPixel = _pixelsPos.y + _pixelSize.y * 0.5f;

	float limitRightCircle = _circlePos.x + _fCircleRadius;
	float limitLeftCircle = _circlePos.x - _fCircleRadius;
	float limitTopCircle = _circlePos.y - _fCircleRadius;
	float limitBottomCircle = _circlePos.y + _fCircleRadius;


	//Como sabemos que hay un punto de corte, se puede calcular el area en base a los valores intermedios de cada eje
	std::vector<float> vIntersectionsX;
	vIntersectionsX.push_back(limitLeftPixel);
	vIntersectionsX.push_back(limitRightPixel);
	vIntersectionsX.push_back(limitLeftCircle);
	vIntersectionsX.push_back(limitRightCircle);

	std::sort(vIntersectionsX.begin(), vIntersectionsX.end());
	MyVec2D intersectionPointsX{ vIntersectionsX[1],vIntersectionsX[2] };

	std::vector<float> vIntersectionsY;
	vIntersectionsY.push_back(limitTopPixel);
	vIntersectionsY.push_back(limitBottomPixel);
	vIntersectionsY.push_back(limitTopCircle);
	vIntersectionsY.push_back(limitBottomCircle);

	std::sort(vIntersectionsY.begin(), vIntersectionsY.end());
	MyVec2D intersectionPointsY{ vIntersectionsY[1],vIntersectionsY[2] };


	//area de interseccion = intersectionPointsX & intersectionPointsY
//Coger el pixel relativo a la posicion del y el punto de corte
	int xPixelMin = intersectionPointsX.x - limitLeftPixel;
	int xPixelMax = intersectionPointsX.y - limitLeftPixel;
	int yPixelMin = intersectionPointsY.x - limitTopPixel;
	int yPixelMax = intersectionPointsY.y - limitTopPixel;


	int xLenghtArea = xPixelMax - xPixelMin;
	int yLenghtArea = yPixelMax - yPixelMin;

	//Iterate the area
	for (unsigned int i = 0; i < yLenghtArea; i++) //Iterate Vertical Pixels Axis
	{
		int yPixel1Index = yPixelMin + i;

		for (unsigned int j = 0; j < xLenghtArea; j++) //Iterate Horizontal Pixels Axis
		{
			int xPixel1Index = xPixelMin + j;

			int pixel1IndexAbsolut = ((yPixel1Index * _pixelSize.x + xPixel1Index) * 4) + 3;

			if (_pixels[pixel1IndexAbsolut] != 0) //Just Check only the Pixels without Alpha
			{
				MyVec2D currentPixelPos{ intersectionPointsX.x + j, intersectionPointsY.x + i };
				if (currentPixelPos.Distance(_circlePos) <= _fCircleRadius)
				{
					return true;
				}
			}
		}
	}

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
	if (!CheckRectRect(_rectPos, _rectSize, _pixelsPos, _pixelSize))
	{
		return false;
	}

	//Puntos de cortes
	float limitRightPixel = _pixelsPos.x + _pixelSize.x * 0.5f;
	float limitLeftPixel = _pixelsPos.x - _pixelSize.x * 0.5f;
	float limitTopPixel = _pixelsPos.y - _pixelSize.y * 0.5f;
	float limitBottomPixel = _pixelsPos.y + _pixelSize.y * 0.5f;

	float limitRightRect = _rectPos.x + _rectSize.x * 0.5f;
	float limitLeftRect = _rectPos.x - _rectSize.x * 0.5f;
	float limitTopRect = _rectPos.y - _rectSize.y * 0.5f;
	float limitBottomRect = _rectPos.y + _rectSize.y * 0.5f;


	//Como sabemos que hay un punto de corte, se puede calcular el area en base a los valores intermedios de cada eje
	std::vector<float> vIntersectionsX;
	vIntersectionsX.push_back(limitLeftPixel);
	vIntersectionsX.push_back(limitRightPixel);
	vIntersectionsX.push_back(limitLeftRect);
	vIntersectionsX.push_back(limitRightRect);

	std::sort(vIntersectionsX.begin(), vIntersectionsX.end());
	MyVec2D intersectionPointsX{ vIntersectionsX[1],vIntersectionsX[2] };

	std::vector<float> vIntersectionsY;
	vIntersectionsY.push_back(limitTopPixel);
	vIntersectionsY.push_back(limitBottomPixel);
	vIntersectionsY.push_back(limitTopRect);
	vIntersectionsY.push_back(limitBottomRect);

	std::sort(vIntersectionsY.begin(), vIntersectionsY.end());
	MyVec2D intersectionPointsY{ vIntersectionsY[1],vIntersectionsY[2] };


	//area de interseccion = intersectionPointsX & intersectionPointsY
	//Coger el pixel relativo a la posicion del y el punto de corte
	int xPixelMin = intersectionPointsX.x - limitLeftPixel;
	int xPixelMax = intersectionPointsX.y - limitLeftPixel;
	int yPixelMin = intersectionPointsY.x - limitTopPixel;
	int yPixelMax = intersectionPointsY.y - limitTopPixel;


	int xLenghtArea = xPixelMax - xPixelMin;
	int yLenghtArea = yPixelMax - yPixelMin;

	//Iterate the Area
	for (unsigned int i = 0; i < yLenghtArea; i++)
	{
		int yPixel1Index = yPixelMin + i;
		int yPixel2Index = yPixelMin + i;

		for (unsigned int j = 0; j < xLenghtArea; j++)
		{
			int xPixel1Index = xPixelMin + j;

			int pixel1IndexAbsolut = ((yPixel1Index * _pixelSize.x + xPixel1Index) * 4) + 3;
			3;

			if (_pixels[pixel1IndexAbsolut] != 0)
			{
				return true;
			}
		}

	}


	return false;

}

bool Collider::CheckPixelsPixels(const MyVec2D& _pixelsPos1, const MyVec2D& _pixelSize1, const uint8_t* _pixels1, const MyVec2D& _pixelsPos2, const MyVec2D& _pixelSize2, const uint8_t* _pixels2) const
{
	if (!CheckRectRect(_pixelsPos1, _pixelSize1, _pixelsPos2, _pixelSize2))
	{
		return false;
	}

	//Puntos de cortes
	float limitRightPixel1 = _pixelsPos1.x + _pixelSize1.x * 0.5f;
	float limitLeftPixel1 = _pixelsPos1.x - _pixelSize1.x * 0.5f;
	float limitTopPixel1 = _pixelsPos1.y - _pixelSize1.y * 0.5f;
	float limitBottomPixel1 = _pixelsPos1.y + _pixelSize1.y * 0.5f;

	float limitRightPixel2 = _pixelsPos2.x + _pixelSize2.x * 0.5f;
	float limitLeftPixel2 = _pixelsPos2.x - _pixelSize2.x * 0.5f;
	float limitTopPixel2 = _pixelsPos2.y - _pixelSize2.y * 0.5f;
	float limitBottomPixel2 = _pixelsPos2.y + _pixelSize2.y * 0.5f;

	//Como sabemos que hay un punto de corte, se puede calcular el area en base a los valores intermedios de cada eje
	std::vector<float> vIntersectionsX;
	vIntersectionsX.push_back(limitLeftPixel1);
	vIntersectionsX.push_back(limitRightPixel1);
	vIntersectionsX.push_back(limitLeftPixel2);
	vIntersectionsX.push_back(limitRightPixel2);

	std::sort(vIntersectionsX.begin(), vIntersectionsX.end());
	MyVec2D xCrossPoints{ vIntersectionsX[1],vIntersectionsX[2] };

	std::vector<float> vIntersectionsY;
	vIntersectionsY.push_back(limitTopPixel1);
	vIntersectionsY.push_back(limitBottomPixel1);
	vIntersectionsY.push_back(limitTopPixel2);
	vIntersectionsY.push_back(limitBottomPixel2);

	std::sort(vIntersectionsY.begin(), vIntersectionsY.end());
	MyVec2D yCrossPoints{ vIntersectionsY[1],vIntersectionsY[2] };

	//area de interseccion = intersectionPointsX & intersectionPointsY
	//Coger el pixel relativo a la posicion de cada sprite y el punto de corte
	int xPixel1Min = xCrossPoints.x - limitLeftPixel1;
	int xPixel1Max = xCrossPoints.y - limitLeftPixel1;
	int yPixel1Min = yCrossPoints.x - limitTopPixel1;
	int yPixel1Max = yCrossPoints.y - limitTopPixel1;

	int xPixel2Min = xCrossPoints.x - limitLeftPixel2;
	int xPixel2Max = xCrossPoints.y - limitLeftPixel2;
	int yPixel2Min = yCrossPoints.x - limitTopPixel2;
	int yPixel2Max = yCrossPoints.y - limitTopPixel2;

	int xLenghtArea = xPixel1Max - xPixel1Min;
	int yLenghtArea = yPixel1Max - yPixel1Min;

	//Iterate the Area
	for (unsigned int i = 0; i < yLenghtArea; i++)
	{
		int yPixel1Index = yPixel1Min + i;
		int yPixel2Index = yPixel2Min + i;

		for (unsigned int j = 0; j < xLenghtArea; j++)
		{
			int xPixel1Index = xPixel1Min + j;
			int xPixel2Index = xPixel2Min + j;

			int pixel1IndexAbsolut = ((yPixel1Index * _pixelSize1.x + xPixel1Index) * 4) + 3;
			int pixel2IndexAbsolut = ((yPixel2Index * _pixelSize2.x + xPixel2Index) * 4) + 3;

			if (_pixels1[pixel1IndexAbsolut] != 0 && _pixels2[pixel2IndexAbsolut] != 0)
			{
				return true;
			}
		}

	}



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
	return other.Collides(m_positionCollider, m_PixelSize, m_Pixels);
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


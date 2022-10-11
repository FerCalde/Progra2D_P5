#pragma once
#include <string>



template<typename T>
std::string stringFromNumber(T val)
{
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}

//void KeyMoveCirculo(GLFWwindow* window, int key, int scancode, int action, int mods);
//void MoverCirculo(double& deltaTime);
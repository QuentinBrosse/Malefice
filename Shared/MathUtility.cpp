#include <cmath>
#include "MathUtility.h"

const float utility::MathUtility::PI = std::acos(-1);

float utility::MathUtility::degreesToRadians(float degrees)
{
	return utility::MathUtility::PI * degrees / 180.f;
}

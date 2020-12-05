#pragma once
#include "GameObjects.h"

float reducedMass(const float m1, const float m2)
{
	if (m1 == 0 || m2 == 0)
		return 0;

	float rm = (m1 * m2) / (m1 + m2);
	return rm;
}

float max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}
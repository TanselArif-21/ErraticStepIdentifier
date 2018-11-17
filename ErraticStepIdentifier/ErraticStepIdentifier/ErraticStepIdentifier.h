#pragma once

class ErraticStepIdentifier
{
public:
	static int zero_crossing_detector(float x[], int length);
	static int value_crossing_detector(float x[], int length, float a);
};

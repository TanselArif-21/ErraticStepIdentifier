// ErraticStepIdentifierProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int zero_crossing_detector(float x[], int length)
{
	// This holds information about the positivity of the current trajectory
	int pos = -1;

	// This holds information about the number of times a crossing event has occurred
	int count = 0;

	if (x[0] > 0)
	{
		pos = 1;
	}
	else if (x[0] < 0)
	{
		pos = -1;
	}
	else
	{
		pos = 0;
	}

	// Loop through x and note the number of times the sign has changed
	for (int i = 1; i < length; i++)
	{
		//# If i < 0 and pos > 0 then we are changing sign from positive to negative
		//# If i > 0 and pos < 0 then we are changing sign from negative to positive
		//# If i < 0 and pos == 0 then we haven't actually crossed zero
		//# If i > 0 and pos == 0 then we haven't actually crossed zero
		if ((x[i] < 0) && (pos > 0))
		{
			count += 1;
			pos = -1;
		}
		else if ((x[i] > 0) and (pos < 0))
		{
			count += 1;
			pos = 1;
		}
		else
		{
			if (pos == 0)
			{
				if (x[i] < 0)
				{
					pos = -1;
				}
				else if (x[i] > 0)
				{
					pos = 1;
				}
			}
		}
	}

	return count;
}


int value_crossing_detector(float x[], int length, float a) 
{

	for (int i = 0; i < length; i++)
	{
		x[i] = x[i] - a;
	}

	return zero_crossing_detector(x, length);
}

int main()
{
	printf("Calling Python to find the sum of 2 and 2.\n");

	cout << "fd" << endl;

	float arr[6] = { 5, 4, 3, 2, 3, -5 };

	int length = sizeof(arr) / sizeof(*arr);

	int count = value_crossing_detector(arr,length,2.5);

	cout << count << endl;

	system("pause");

    return 0;
}

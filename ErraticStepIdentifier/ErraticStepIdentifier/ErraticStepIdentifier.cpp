// ErraticStepIdentifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include "ErraticStepIdentifier.h"


using namespace std;

// A function to sort a float array x given its size
float* SortArray(float* x, int size)
{
	// The result float array
	float* result = new float[size];

	// If the size is 1 return it
	if (size == 1)
	{
		result[0] = x[0];
		return result;
	}

	// We need the mid point of the array
	int mid = int(size / 2);

	// The current array is split in two
	float* x1;
	float* x2;

	float* temp = new float[mid];
	float* temp2 = new float[size - mid];

	for (int i = 0; i < mid; i++)
	{
		temp[i] = x[i];
	}

	for (int i = mid; i < size; i++)
	{
		temp2[i - mid] = x[i];
	}

	// Get the sorted first half of the array and the sorted second half
	x1 = SortArray(temp, mid);
	x2 = SortArray(temp2, size - mid);

	int i = 0;
	int j = 0;
	int count = 0;

	// Combine the two arrays while considering order
	while ((i < mid) && (j < size - mid))
	{
		if (x1[i] > x2[j])
		{
			result[count] = x1[i];
			i++;
			count++;
		}
		else
		{
			result[count] = x2[j];
			j++;
			count++;
		}
	}

	// The remaining array is appended onto the end
	if (i == mid)
	{
		while (j < size - mid)
		{
			result[count] = x2[j];
			j++;
			count++;
		}
	}
	else
	{
		while (i < mid)
		{
			result[count] = x1[i];
			i++;
			count++;
		}
	}

	// Clean up
	delete(temp);
	delete(temp2);
	delete(x1);
	delete(x2);

	temp = NULL;
	temp2 = NULL;
	x1 = NULL;
	x2 = NULL;

	return result;
}

// A function to split a string by a delimiter
float* ErraticStepIdentifier::splitByDelimiter(string s, char delim)
{
	// First count the occurrence of the delimiter in the string
	int count = std::count(s.begin(), s.end(), ',');

	// Instantiate an array of this size (note that the size is the number of delimiters + 1)
	float *arr = new float[count + 1];

	// Get the substring between each delimiter and save it into arr
	int index = 0;
	int num = 0;
	while (s.length() > 0)
	{
		index = s.find(delim);
		if (index == -1)
		{
			arr[num] = stof(s);
			s = "";
		}
		else
		{
			arr[num] = stof(s.substr(0, index));
			s = s.substr(index + 1, s.length());
		}

		num++;
	}

	return arr;
}

// A function to get the time stamp from a string (the first entry before the first delimiter)
string* ErraticStepIdentifier::getTimeStamp(string s, char delim)
{
	// First count the occurrence of the delimiter in the string
	int count = std::count(s.begin(), s.end(), ',');

	// Instantiate an array of this size (note that the size is the number of delimiters + 1)
	string *arr = new string[count + 1];

	int index = 0;
	int num = 0;

	// Get the first entry and store it into arr
	index = s.find(delim);
	if (index == -1)
	{
		arr[num] = stof(s);
		s = "";
	}
	else
	{
		arr[num] = s.substr(0, index);
		s = s.substr(index + 1, s.length());
	}

	return arr;
}

// A function to get the distance and heading from a file given a delimiter
vector<float*> ErraticStepIdentifier::GetCoordsFromFile(string fileName, char delim)
{
	vector <float*> lines;

	string line;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			float* arr;

			arr = splitByDelimiter(line, ',');

			lines.push_back(arr);
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}

	return lines;
}

// A function to get the time stamps from a file given a delimiter
vector<string*> ErraticStepIdentifier::GetTimeStampsFromFile(string fileName, char delim)
{
	vector <string*> lines;

	string line;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string* arr;

			arr = getTimeStamp(line, ',');

			lines.push_back(arr);
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file\n";
	}

	return lines;
}

// A function to round a floating point number to a given number of decimal places
float ErraticStepIdentifier::roundFloat(float f, int places = 2)
{
	if (places >= 0)
	{
		int factor = 1;
		for (int i = 0; i < places; i++)
		{
			factor *= 10;
		}

		return floor(f * factor + 0.5) / factor;
	}
	else
	{
		return 0.0f;
	}

	float roundedf = floor(f * 100 + 0.5) / 100;
}

// A function to return the number of times a signal given by x crosses 0
int ErraticStepIdentifier::zero_crossing_detector(float x[], int length)
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
		else if ((x[i] > 0) && (pos < 0))
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

// A function to return the number of times a signal given by x crosses  a user given value a
int ErraticStepIdentifier::value_crossing_detector(float x[], int length, float a)
{

	for (int i = 0; i < length; i++)
	{
		x[i] = x[i] - a;
	}

	return ErraticStepIdentifier::zero_crossing_detector(x, length);
}

// A function to return the Erraticity of a particular signal. Erraticity here is defined by 
// total number of value crossing events / total distance. This way, a larger erraticity corresponds to 
// a greater number of value crossing event in relation to the total distance travelled
float ErraticStepIdentifier::Erraticity(vector<float*> x)
{
	// This function returns the erraticity of the path/signal
	float* radianArray = new float[x.size()];

	float totalDistance = 0;
	float averageDirection = 0;
	int valueCrossingEvents = 0;

	for (int i = 0; i < x.size(); i++)
	{
		totalDistance += x[i][1];
		averageDirection += x[i][2];
		radianArray[i] = x[i][2];
	}

	averageDirection /= x.size();



	valueCrossingEvents = ErraticStepIdentifier::value_crossing_detector(radianArray, x.size(), averageDirection);

	delete(radianArray);
	radianArray = NULL;

	// Now return the erraticity

	return valueCrossingEvents/totalDistance;
}

// A function to return the Erraticity of a particular signal. Erraticity here is defined by 
// total number of value crossing events / total distance. This way, a larger erraticity corresponds to 
// a greater number of value crossing event in relation to the total distance travelled.
// The sensitivity is defined as the decimal place to register a radial change.
float ErraticStepIdentifier::Erraticity(vector<float*> x, int sensitivity)
{
	// This function returns the erraticity of the path/signal
	float* radianArray = new float[x.size()];

	float totalDistance = 0;
	float averageDirection = 0;
	int valueCrossingEvents = 0;

	for (int i = 0; i < x.size(); i++)
	{
		totalDistance += x[i][1];
		averageDirection += roundFloat(x[i][2], sensitivity);
		radianArray[i] = x[i][2];
	}

	averageDirection /= x.size();



	valueCrossingEvents = ErraticStepIdentifier::value_crossing_detector(radianArray, x.size(), averageDirection);

	delete(radianArray);
	radianArray = NULL;

	// Now return the erraticity

	return valueCrossingEvents / totalDistance;
}

// A function to get the erraticities from a vector of floats. Size specifies
// the number of time points to consider
float* ErraticStepIdentifier::GetErraticitiesArray(vector<float*> x, int size = 5)
{
	float* elasticityArray = new float[x.size() - size];

	for (int i = 0; i < int(x.size() - size); i += 1)
	{
		vector <float*> lines;
		for (int j = i; j < i + size; j++)
		{
			lines.push_back(x[j]);
		}

		elasticityArray[i] = ErraticStepIdentifier::Erraticity(lines);
	}

	return elasticityArray;
}

// A function to get the erraticities from a vector of floats. Size specifies
// the number of time points to consider.
// The sensitivity is defined as the decimal place to register a radial change.
float* ErraticStepIdentifier::GetErraticitiesArray(vector<float*> x, int sensitivity, int size)
{
	float* elasticityArray = new float[x.size() - size];

	for (int i = 0; i < int(x.size() - size); i += 1)
	{
		vector <float*> lines;
		for (int j = i; j < i + size; j++)
		{
			lines.push_back(x[j]);
		}

		elasticityArray[i] = ErraticStepIdentifier::Erraticity(lines, sensitivity);
	}

	return elasticityArray;
}

// A function to get the sorted erraticities from a vector of floats. Size specifies
// the number of time points to consider.
// The sensitivity is defined as the decimal place to register a radial change.
float* ErraticStepIdentifier::GetSortedErraticitiesArray(vector<float*> x, int size = 5)
{
	float* erraticityArray = new float[x.size() - size];

	for (int i = 0; i < int(x.size() - size); i += 1)
	{
		vector <float*> lines;
		for (int j = i; j < i + size; j++)
		{
			lines.push_back(x[j]);
		}

		erraticityArray[i] = ErraticStepIdentifier::Erraticity(lines);
	}

	return SortArray(erraticityArray, x.size() - size);
}

// A function to calculate the erraticities and saves the file to fileOutput
void ErraticStepIdentifier::ProduceErraticitiesFile(string fileInput, string fileOutput, int sensitivity, int size = 5)
{
	vector <float*> lines;
	vector <string*> lines2;

	lines = ErraticStepIdentifier::GetCoordsFromFile(fileInput, ',');
	lines2 = ErraticStepIdentifier::GetTimeStampsFromFile(fileInput, ',');

	float* f = ErraticStepIdentifier::GetErraticitiesArray(lines, sensitivity, size);

	ofstream myfile(fileOutput);
	if (myfile.is_open())
	{
		for (int i = 0; i < lines.size() - 5; i++)
		{
			myfile << lines2[i][0] << "," << f[i] << endl;
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	delete(f);
	f = NULL;
}

int main(int argc, char** argv)
{
	string fileName;
	string fileName2;
	int sensitivity;
	int size;

	vector <float*> lines;
	vector <string*> lines2;

	if (argc < 2)
	{
		printf("Please provide a file.\n");
		system("pause");

		return 0;
	}

	if (argc == 2)
	{
		printf("Starting.\n");

		fileName = argv[1];
		fileName2 = fileName + "output";

		ErraticStepIdentifier::ProduceErraticitiesFile(fileName, fileName2, 0, 5);
	}
	else if (argc == 3)
	{
		printf("Starting.\n");

		fileName = argv[1];
		fileName2 = argv[2];

		ErraticStepIdentifier::ProduceErraticitiesFile(fileName, fileName2, 0, 5);
	}
	else if (argc == 4)
	{
		printf("Starting.\n");

		fileName = argv[1];
		fileName2 = argv[2];
		sensitivity = stof(argv[3]);

		ErraticStepIdentifier::ProduceErraticitiesFile(fileName, fileName2, sensitivity, 5);
	}
	else if (argc > 4)
	{
		printf("Starting.\n");

		fileName = argv[1];
		fileName2 = argv[2];
		sensitivity = stoi(argv[3]);
		size = stoi(argv[4]);

		ErraticStepIdentifier::ProduceErraticitiesFile(fileName, fileName2, sensitivity, size);
	}
	else
	{
		printf("Starting.\n");

		fileName = argv[1];
		fileName2 = fileName + "output";

		ErraticStepIdentifier::ProduceErraticitiesFile(fileName, fileName2, 0, 5);
	}

	system("pause");

    return 0;
}

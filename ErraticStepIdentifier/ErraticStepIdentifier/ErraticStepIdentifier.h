#pragma once

#include <string>

using namespace std;

class ErraticStepIdentifier
{
public:
	class Trajectory;

	static float roundFloat(float f, int places);
	static int zero_crossing_detector(float x[], int length);
	static int value_crossing_detector(float x[], int length, float a);
	static float* splitByDelimiter(string s, char delim);
	static string* splitByDelimiterString(string s, char delim);
	static string* getTimeStamp(string s, char delim);
	static vector<float*> GetCoordsFromFile(string fileName, char delim);
	static void GetTrajectoryFromFile(Trajectory t, string fileName, char delim);
	static vector<string*> GetTimeStampsFromFile(string fileName, char delim);
	static float Erraticity(vector<float*> x);
	static float Erraticity(vector<float*> x, int sensitivity);
	static float* GetErraticitiesArray(vector<float*> x, int size);
	static float* GetErraticitiesArray(vector<float*> x, int sensitivity, int size);
	static float* GetSortedErraticitiesArray(vector<float*> x, int sensitivity);
	static void ProduceErraticitiesFile(string fileInput, string fileOutput, int sensitivity, int size);
};

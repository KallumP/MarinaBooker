#pragma once
#include <iostream>

class TimeStamp {


public:
	TimeStamp();
	TimeStamp(std::string _date);
	~TimeStamp();

	void AdjustLength(float newLength);
	float GetLengthUsed();
	std::string GetDate();

	static const int MAX_LENGTH = 150;

private:

	std::string date;
	float lengthUsed;

};


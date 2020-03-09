#pragma once
#include <iostream>

class TimeStamp {


public:
	TimeStamp();
	TimeStamp(std::string);
	~TimeStamp();

	void AdjustLength(float);
	float GetLengthUsed();
	std::string GetDate();

	static const int MAX_LENGTH = 150;

private:

	std::string date;
	float lengthUsed;

};


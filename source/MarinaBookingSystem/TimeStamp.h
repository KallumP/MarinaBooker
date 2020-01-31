#pragma once
class TimeStamp {


public:
	TimeStamp();
	TimeStamp(int _month);
	~TimeStamp();

	void AdjustLength(float newLength);
	float GetLengthUsed();
	int GetMonthNumber();

	static const int MAX_LENGTH = 150;

private:

	int monthNumber;
	float lengthUsed;

};


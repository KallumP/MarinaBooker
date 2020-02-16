#include <iostream>

#include "TimeStamp.h"

TimeStamp::TimeStamp() {
}

TimeStamp::TimeStamp(std::string _date) {
	
	date = _date;
	lengthUsed = 0;
}


TimeStamp::~TimeStamp() {
}

//adjusts the amount of length used on this timestamp
void TimeStamp::AdjustLength(float newLength) {
	lengthUsed += newLength;
}

//returns the length used in this current timestamp
float TimeStamp::GetLengthUsed() {
	return lengthUsed;
}

std::string TimeStamp::GetDate() {

	return date;
}
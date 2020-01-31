#include "TimeStamp.h"

TimeStamp::TimeStamp(){

}

TimeStamp::TimeStamp(int _month){
	monthNumber = _month;
	lengthUsed = 0;
}


TimeStamp::~TimeStamp(){
}

//adjusts the amount of length used on this timestamp
void TimeStamp::AdjustLength(float newLength){
	lengthUsed += newLength;
}

//returns the length used in this current timestamp
float TimeStamp::GetLengthUsed() {
	return lengthUsed;
}

int TimeStamp::GetMonthNumber() {

	return monthNumber;
}
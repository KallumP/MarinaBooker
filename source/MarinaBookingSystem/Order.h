#pragma once
#include "TimeStamp.h"

#include <iostream>
#include <vector>

struct TimeStampIndexes {
	TimeStampIndexes(int _start, int _end) {
		start = _start;
		end = _end;
	}
	TimeStampIndexes() {
		start = 0;
		end = 0;
	}
	int start;
	int end;
};

struct Order {

	float depth;
	float length;
	std::string name;
	std::string boatName;
	TimeStampIndexes timeings;
	float cost;
};




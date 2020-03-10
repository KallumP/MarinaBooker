#pragma once
#include <iostream>

class Boat {

public:
	Boat();
	Boat(float, float, int, int, std::string);
	~Boat();

	int GetEnter();
	int GetLeave();
	std::string GetName();

private:
	float length;
	float depth;

	int entryMonth;
	int leaveMonth;

	std::string name;
};


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

	void Leave(bool);
	void Return();

private:
	float length;
	float depth;

	int entryMonth;
	int leaveMonth;

	float linePosition;

	std::string name;
};


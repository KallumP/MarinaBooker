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

class Narrow : Boat {
	Narrow(float, float, int, int, std::string);
};
class Sailing : Boat {
	Sailing(float, float, int, int, std::string);
};
class Motor : Boat {
	Motor(float, float, int, int, std::string);
};




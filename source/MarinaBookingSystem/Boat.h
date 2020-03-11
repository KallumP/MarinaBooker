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
	void SetName(std::string);
	int GetLength();

private:
	float length;
	float depth;

	int entryMonth;
	int leaveMonth;

	std::string name;
};

class Narrow : public Boat {
public:
	Narrow(float, float, int, int, std::string);
};
class Sailing : public Boat {
public:
	Sailing(float, float, int, int, std::string);
};
class Motor : public Boat {
public:
	Motor(float, float, int, int, std::string);
};




#pragma once
#include <iostream>

class Boat {

public:
	Boat();
	Boat(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name);
	~Boat();

	int GetEnter();
	int GetLeave();
	std::string GetName();

	void Leave(bool comeBack);
	void Return();

private:
	float length;
	float depth;

	int entryMonth;
	int leaveMonth;

	float linePosition;

	std::string name;
};


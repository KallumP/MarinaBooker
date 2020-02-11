#pragma once
class Boat {

public:
	Boat();
	Boat(float _length, float _depth, int _entryMonth, int _leaveMonth);
	~Boat();

	int GetEnter();

	void Leave(bool comeBack);
	void Return();

private:
	float length;
	float depth;

	int entryMonth;
	int leaveMonth;

	float linePosition;
};


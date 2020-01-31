#pragma once
class Boat {

public:
	Boat();
	~Boat();

	void Leave(bool comeBack);
	void Return();

private:
	float width, length, depth;

	float linePosition;



};


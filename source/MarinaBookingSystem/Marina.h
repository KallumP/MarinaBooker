#pragma once
#include "TimeStamp.h"
#include "Boat.h"

#include <iostream>
#include <vector>

class Marina {


public:

	Marina();
	Marina(std::vector<TimeStamp>);
	~Marina();

	void SpawnBoat(Boat);
	void NextMonth(int);
	bool Empty();
private:

	void RemoveBoat(int, bool);
	void ReturnAllHoldBoats();
	void Draw();
	void MoveCursor(int, int);

	std::vector<Boat> marinaBoats;
	std::vector<Boat> holdingBoats;
	int currentMonth;
	std::vector<TimeStamp> timeTable;
};


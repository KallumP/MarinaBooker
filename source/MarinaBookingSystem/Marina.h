#pragma once
#include <iostream>
#include <vector>

#include "Boat.h"

class Marina {


public:

	Marina();
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
};


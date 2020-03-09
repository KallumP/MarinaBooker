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

private:

	void RemoveBoat(int, bool);
	void ReturnAllHoldBoats();
	void Draw();

	std::vector<Boat> marinaBoats;
	std::vector<Boat> holdingBoats;
};


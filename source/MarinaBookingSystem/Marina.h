#pragma once
#include <iostream>
#include <vector>

#include "Boat.h"

class Marina {


public:

	Marina();
	~Marina();

	void SpawnBoat(Boat toSpawn); 
	void NextMonth(int newMonth);

private:
	
	void RemoveBoat(Boat toRemove);
	void ReturnAllHoldBoats();

	std::vector<Boat> marinaBoats;
	std::vector<Boat> holdingBoats;
};


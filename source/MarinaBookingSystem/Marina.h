#pragma once
#include <iostream>
#include <vector>

#include "Boat.h"

class Marina {


public:

	Marina();
	~Marina();

	void SpawnBoat(Boat toSpawn);



private:

	std::vector<Boat> marinaBoats;
	std::vector<Boat> holdingBoats;


};


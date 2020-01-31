#pragma once
#include <iostream>
#include <vector>

#include "Boat.h"

class Environment {

public:

	Environment();
	~Environment();


private:

	void Loop();
	void Proccess();
	void Draw();
	void AddBoat();
	void RemoveBoat();

	//Marina marina;
	std::vector<Boat> entryOrder;
	bool running;
};


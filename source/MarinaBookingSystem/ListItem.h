#pragma once

#include "Boat.h"

class ListItem {

public: 

	
	ListItem();
	ListItem(Boat _boat);

	void SetNextPointer(ListItem* next);
	void SetPrevPointer(ListItem* next);

	int GetBoatEnter();
private:
	Boat boat;

	ListItem* nextBoat;
	ListItem* prevBoat;

};





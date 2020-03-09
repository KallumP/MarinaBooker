#pragma once
#include "Boat.h"

class ListItem {

public:


	ListItem();
	ListItem(Boat);

	void SetNextPointer(ListItem*);
	void SetPrevPointer(ListItem*);
	ListItem* GetPrevPointer();
	ListItem* GetNextPointer();

	Boat GetBoat();
private:
	Boat boat;

	ListItem* nextBoat;
	ListItem* prevBoat;

};





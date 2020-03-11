#pragma once
#include "Boat.h"

class ListItem {

public:

	ListItem();
	ListItem(Boat);

	void SetNextPointer(ListItem*);
	void SetPrevPointer(ListItem*);
	ListItem* GetNextPointer();
	ListItem* GetPrevPointer();

	Boat GetBoat();

private:
	Boat boat;

	ListItem* next;
	ListItem* prev;

};





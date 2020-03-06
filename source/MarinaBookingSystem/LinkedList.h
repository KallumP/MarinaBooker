#pragma once
#include "ListItem.h"

#include <vector>

class LinkedList {

public:

	LinkedList();
	LinkedList(int size);

	void AddItem(ListItem newItem);
	void SortItem(ListItem* toAdd, ListItem* current);
	void InsertFirstItem(ListItem* toAdd);
	void InsertFirstLocation(ListItem* newItem, ListItem* next);
	void InsertCenterLocation(ListItem* toAdd, ListItem* prev, ListItem* next);
	void InsertLastLocation(ListItem* toAdd, ListItem* prev);

	void DeleteItem(ListItem* toRemove);

	void OutputBoats(bool forward);

//private:

	std::vector<ListItem> boatSpawnOrder;
	int vectorInsert;
	ListItem* start;
	ListItem* end;
};


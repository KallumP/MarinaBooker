#pragma once
#include "ListItem.h"

#include <vector>


class LinkedList {

public:

	LinkedList();

	void AddItem(ListItem toAdd);
	void SortItem(ListItem* toAdd, ListItem* current);
	void InsertFirstItem(ListItem* toAdd);
	void InsertFirstLocation(ListItem* newItem, ListItem* next);
	void InsertCenterLocation(ListItem* toAdd, ListItem* prev, ListItem* next);
	void InsertLastLocation(ListItem* toAdd, ListItem* prev);

	void DeleteItem();

	void Output();
	void TraverseList(ListItem* item);

private:

	std::vector<ListItem> spawnOrder;
	ListItem* start;
};


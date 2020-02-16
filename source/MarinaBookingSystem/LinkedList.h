#pragma once
#include "ListItem.h"

#include <vector>


class LinkedList {

public:

	LinkedList();
	LinkedList(int size);

	void AddItem(Boat toAdd);
	void AddItem(ListItem newItem);
	void AddItem(int length, int depth, int start, int end, std::string boatName);

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
	int vectorInsert;
	ListItem* start;
};


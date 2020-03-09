#pragma once
#include "ListItem.h"

#include <vector>

class LinkedList {

public:

	LinkedList();
	LinkedList(int);

	void AddItem(ListItem);
	void SortItem(ListItem*, ListItem*);
	void InsertFirstItem(ListItem*);
	void InsertFirstLocation(ListItem*, ListItem*);
	void InsertCenterLocation(ListItem*, ListItem*, ListItem*);
	void InsertLastLocation(ListItem*, ListItem*);

	void DeleteItem(ListItem*);

	void OutputBoats(bool);

	//private:

	std::vector<ListItem> boatSpawnOrder;
	int vectorInsert;
	ListItem* start;
	ListItem* end;
};


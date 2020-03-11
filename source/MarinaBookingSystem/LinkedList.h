#pragma once
#include "ListItem.h"

#include <vector>

class LinkedList {

public:
	LinkedList();
	~LinkedList();

	void AddItem(ListItem);
	void DeleteItem(ListItem*);
	void OutputBoats(bool);

	ListItem* GetStart();
	ListItem* GetEnd();

private:
	void SortItem(ListItem*, ListItem*);
	void InsertFirstItem(ListItem*);
	void InsertFirstLocation(ListItem*, ListItem*);
	void InsertCenterLocation(ListItem*, ListItem*, ListItem*);
	void InsertLastLocation(ListItem*, ListItem*);

	ListItem* start;
	ListItem* end;
};


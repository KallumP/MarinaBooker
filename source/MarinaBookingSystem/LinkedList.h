#pragma once
#include "ListItem.h"

#include <vector>


class LinkedList {

public:

	LinkedList();

	void AddItem(ListItem toAdd);
	void SortFirstItem(ListItem toAdd);
	void SortItem(ListItem toAdd, ListItem current);

	void DeleteItem();

	void Output();
	void TraverseList(ListItem item);

private:

	std::vector<ListItem> spawnOrder;
	ListItem start;
	ListItem end;
};


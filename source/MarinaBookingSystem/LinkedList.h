#pragma once
#include "ListItem.h"

#include <vector>


class LinkedList {

public:

	LinkedList();

	void AddItem(ListItem toAdd);
	void SortFirstItem(ListItem toAdd);
	void SortItem(ListItem toAdd);

	void DeleteItem();

private:

	std::vector<ListItem> spawnOrder;
	int startIndex;
	int endIndex;
};


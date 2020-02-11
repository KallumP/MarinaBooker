#include "LinkedList.h"
#include "ListItem.h"

LinkedList::LinkedList() {

}

void LinkedList::AddItem(ListItem toAdd) {
	
	//checks if there was anything in the linked list already
	if (spawnOrder.size() == 0)

		SortFirstItem(toAdd);

	else

		SortItem(toAdd);
}

void LinkedList::SortFirstItem(ListItem toAdd) {
	
	//lets the linked list know to start at the this value
	startIndex = 0;

	//lets the linked list know that the list ends at this value
	endIndex = 0;

	//lets the linked list know that this is the last item
	toAdd.SetNextPointer(nullptr);
	
	//lets the linked list know that there are no previous items
	toAdd.SetPrevPointer(nullptr);

	//adds the listitem to the linked list
	spawnOrder.push_back(toAdd);
}

void LinkedList::SortItem(ListItem toAdd) {
	
	//if (toAdd.GetBoatEnter() <)

}

void LinkedList::DeleteItem() {

}
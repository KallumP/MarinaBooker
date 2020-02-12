#include "LinkedList.h"
#include "ListItem.h"

LinkedList::LinkedList() {

}

void LinkedList::AddItem(ListItem toAdd) {

	//checks if there was anything in the linked list already
	if (spawnOrder.size() == 0)

		SortFirstItem(toAdd);

	else

		SortItem(toAdd, start);
}

//Sorts the new item as a first item
void LinkedList::SortFirstItem(ListItem toAdd) {

	//lets the linked list know to start at the this value
	start = toAdd;

	//lets the linked list know that the list ends at this value
	end = toAdd;

	//lets the linked list know that this is the last item
	toAdd.SetNextPointer(nullptr);

	//lets the linked list know that there are no previous items
	toAdd.SetPrevPointer(nullptr);

	//adds the listitem to the linked list
	spawnOrder.push_back(toAdd);
}

//sorts the item into the list
void LinkedList::SortItem(ListItem newItem, ListItem current) {

	//checks to see if the item being added goes before the current item being checked
	if (newItem.GetBoat().GetEnter() < current.GetBoat().GetEnter()) {

		//sets the new item's next pointer to the current item's next pointer
		newItem.SetNextPointer(&current);

		//sets the previous pointer to now point to the current item's pointer
		newItem.SetPrevPointer(current.GetPrevPointer());

		//sets the current item to point to the new item
		current.SetPrevPointer(&newItem);

		//checks to see if the current item being checked was the first in the list
		if (current.GetPrevPointer() == nullptr)

			//sets the starting point at the new item
			start = newItem;

	} else {

		//checks to see if there were more items to sort through
		if (current.GetNextPointer() != nullptr) {

			//calls the sort function on the next item in the linked list
			SortItem(newItem, *current.GetNextPointer());

		} else {

			//sets the current item to point to the new item
			current.SetNextPointer(&newItem);

			//sets the new item's previous item pointer to point to the current item
			newItem.SetPrevPointer(&current);
		}

	}

	spawnOrder.push_back(newItem);
}

//goes through the deleting protocol
void LinkedList::DeleteItem() {

}

void LinkedList::Output() {

	//starts traversing the list from the first item
	TraverseList(start);
}

void LinkedList::TraverseList(ListItem item) {

	//outputs the name and the entry time of the current item's boat
	std::cout << "Boat: " << item.GetBoat().GetName() << " will be entering at: " << item.GetBoat().GetEnter() << std::endl;

	//checks to see if there were more in the list to traverse to
	if (item.GetNextPointer() != nullptr)
		TraverseList(*item.GetNextPointer());

}
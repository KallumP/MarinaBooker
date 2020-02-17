#include "LinkedList.h"
#include "ListItem.h"

#include <vector>

//constructor
LinkedList::LinkedList() {
}

//constructor
LinkedList::LinkedList(int size) {

	//sets up the linked list to a certain size
	boatSpawnOrder.resize(size);

	//sets up the insert position for the vector to be 0
	vectorInsert = 0;

	//sets the start to point to nothing
	start = nullptr;

	//sets the end to point to nothing
	end = nullptr;
}

//adds a new item
void LinkedList::AddItem(ListItem newItem) {

	//adds a new list item to the linked list
	boatSpawnOrder[vectorInsert] = newItem;

	//starts the sort sequence
	SortItem(&boatSpawnOrder[vectorInsert], start);

	//updates the insert position
	vectorInsert++;
}

//sorts the item into the list
void LinkedList::SortItem(ListItem* newItem, ListItem* current) {

	//checks to see if there was nothing in the list already
	if (current == nullptr)

		InsertFirstItem(newItem);

	//checks if the newItem goes before the current item being checked and the current item was first in the list
	else if (newItem->GetBoat().GetEnter() < current->GetBoat().GetEnter() && current->GetPrevPointer() == nullptr)

		InsertFirstLocation(newItem, current);

	//checks if the newItem goes before the current item being checked and the current item was not first in the list
	else if (newItem->GetBoat().GetEnter() < current->GetBoat().GetEnter() && current->GetPrevPointer() != nullptr)

		InsertCenterLocation(newItem, current->GetPrevPointer(), current);

	//checks to see if the newItem goes after the current item being checked, and if the current item was the last in the list
	else if (newItem->GetBoat().GetEnter() >= current->GetBoat().GetEnter() && current->GetNextPointer() == nullptr)

		InsertLastLocation(newItem, current);

	else

		//recursivley calls the sort function on the next item in the linked list
		SortItem(newItem, current->GetNextPointer());
}

//inserts the new item as a first item 
void LinkedList::InsertFirstItem(ListItem* newItem) {

	//lets the linked list know that the new item is the last item
	newItem->SetNextPointer(nullptr);

	//lets the linked list know that there are no previous items
	newItem->SetPrevPointer(nullptr);

	//lets the linked list know to start at the new item
	start = newItem;

	//lest the linked list know that the new item is also the end
	end = newItem;
}

//inserrts the new item into the first spot of the list (only needs the newItem)
void LinkedList::InsertFirstLocation(ListItem* newItem, ListItem* next) {

	//sets the new item's next pointer to point to the current item
	newItem->SetNextPointer(next);

	//sets the current item's previous pointer to point to the new item
	next->SetPrevPointer(newItem);

	//sets the starting point at the new item
	start = newItem;
}

//inserts the new item into the center of the list (needs the newItem, the previousItem and the nextItem)
void LinkedList::InsertCenterLocation(ListItem* newItem, ListItem* prev, ListItem* next) {

	//sets the previous item's next pointer to point to the new item
	prev->SetNextPointer(newItem);

	//sets the new item's prev pointer to piont to the previous item
	newItem->SetPrevPointer(prev);

	//sets the new item's next pointer to point to the next item
	newItem->SetNextPointer(next);

	//sets the next item's previous pointer to point to the new item
	next->SetPrevPointer(newItem);
}

//inserts the new item into the end of the list (needs the newItem and the prvious item
void LinkedList::InsertLastLocation(ListItem* newItem, ListItem* prev) {

	//sets the previous item's next pointer to point to the new item
	prev->SetNextPointer(newItem);

	//sets the new item's prev pointer to piont to the previous item
	newItem->SetPrevPointer(prev);

	//sets up where the end of the list is
	end = newItem;
}

//goes through the deleting protocol
void LinkedList::DeleteItem(ListItem* toRemove) {

	//checks to see if this was the first item
	if (toRemove->GetPrevPointer() == nullptr) {

		//sets the start to the next item
		start = toRemove->GetNextPointer();

		//sets the next item's previous item to the current item's previous item
		toRemove->GetNextPointer()->SetPrevPointer(toRemove->GetPrevPointer());
	}

	//loops through all the orders
	for (int i = 0; i < boatSpawnOrder.size(); i++) {

		//checks to see if the address of the toRemove is the same as the current loop one
		if (&boatSpawnOrder[i] == toRemove) {

			//deletes the order
			boatSpawnOrder.erase(boatSpawnOrder.begin() + i);

			//stops searching
			break;
		}
	}
}

//starts the output of the linked list
void LinkedList::OutputBoats(bool forward) {

	//declares a list item to hold what item to call the traversal on
	ListItem* next;

	//checks to see if the traversal should be forward or backwards
	if (forward) {

		//sets the traversal at thes start of the list
		next = start;

		std::cout << "Forward Traversal" << std::endl;


		//keeps traversing until there are no more list items left
		while (next != nullptr){

			//outputs the name and the entry time of the current item's boat
			std::cout << "Boat: " << next->GetBoat().GetName() << " will be entering at: " << next->GetBoat().GetEnter() << std::endl;

			//traverses the list
			next = next->GetNextPointer();
		}

		std::cout << std::endl << std::endl << std::endl;
			

	} else if (!forward && end != nullptr) {
		
		//sets the traversal at the end of the list
		next = end;

		std::cout << "Backward Traversal" << std::endl;

		while (next != nullptr) {

			//outputs the name and the entry time of the current item's boat
			std::cout << "Boat: " << next->GetBoat().GetName() << " will be entering at: " << next->GetBoat().GetEnter() << std::endl;

			//gets the previous item
			next = next->GetPrevPointer();
		}

		std::cout << std::endl << std::endl << std::endl;
	}
}
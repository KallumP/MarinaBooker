#include "LinkedList.h"
#include "ListItem.h"

LinkedList::LinkedList() {
}

LinkedList::LinkedList(int size) {

	//sets up the linked list to a certain size
	spawnOrder.resize(size);

	//sets up the insert position for the vector to be 0
	vectorInsert = 0;

	//sets the start to point to nothing
	start = nullptr;
}

//adds a new item using a boat
void LinkedList::AddItem(Boat _boat) {

	//adds a new list item to the linked list
	spawnOrder[vectorInsert] = ListItem(_boat);

	//starts the sort sequence
	SortItem(&spawnOrder[vectorInsert], start);

	//updates the insert position
	vectorInsert++;
}

//adds a new item
void LinkedList::AddItem(ListItem newItem) {

	//adds a new list item to the linked list
	spawnOrder[vectorInsert] = newItem;

	//starts the sort sequence
	SortItem(&spawnOrder[vectorInsert], start);

	//updates the insert position
	vectorInsert++;
}

//adds a new item using the raw variables
void LinkedList::AddItem(int length, int depth, int startTime, int endTime, std::string boatName) {

	//adds a new list item to the linked list
	spawnOrder[vectorInsert] = ListItem(Boat(length, depth, startTime, endTime, boatName));

	//starts the sort sequence
	SortItem(&spawnOrder[vectorInsert], start);

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
	else if (newItem->GetBoat().GetEnter() > current->GetBoat().GetEnter() && current->GetNextPointer() == nullptr)

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
}

//goes through the deleting protocol
void LinkedList::DeleteItem() {

}

void LinkedList::Output() {

	//starts traversing the list from the first item
	TraverseList(start);
}

void LinkedList::TraverseList(ListItem* item) {

	//outputs the name and the entry time of the current item's boat
	std::cout << "Boat: " << item->GetBoat().GetName() << " will be entering at: " << item->GetBoat().GetEnter() << std::endl;

	//checks to see if there were more in the list to traverse to
	if (item->GetNextPointer() != nullptr)
		TraverseList(item->GetNextPointer());

}
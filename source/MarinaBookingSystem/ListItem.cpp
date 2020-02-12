#include "ListItem.h"
#include "Boat.h"


ListItem::ListItem() {
	nextBoat = nullptr;
	prevBoat = nullptr;
}

ListItem::ListItem(Boat _boat) {
	boat = _boat;
	nextBoat = nullptr;
	prevBoat = nullptr;
}

Boat ListItem::GetBoat() {
	return boat;
}


ListItem* ListItem::GetNextPointer() {
	return nextBoat;
}

void ListItem::SetNextPointer(ListItem* next) {
	nextBoat = next;
}

ListItem* ListItem::GetPrevPointer() {
	return prevBoat;
}

void ListItem::SetPrevPointer(ListItem* prev) {
	prevBoat = prev;
}


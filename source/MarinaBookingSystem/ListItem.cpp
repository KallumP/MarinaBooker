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

int ListItem::GetBoatEnter() {
	return boat.GetEnter();
}

void ListItem::SetNextPointer(ListItem* next) {
	nextBoat = next;
}

void ListItem::SetPrevPointer(ListItem* prev) {
	prevBoat = prev;
}


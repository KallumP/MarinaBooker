#include "ListItem.h"
#include "Boat.h"

ListItem::ListItem() {
	next = nullptr;
	prev = nullptr;
}

ListItem::ListItem(Boat _boat) {
	boat = _boat;
	next = nullptr;
	prev = nullptr;
}

Boat ListItem::GetBoat() {
	return boat;
}


ListItem* ListItem::GetNextPointer() {
	return next;
}

void ListItem::SetNextPointer(ListItem* _next) {
	next = _next;
}

ListItem* ListItem::GetPrevPointer() {
	return prev;
}

void ListItem::SetPrevPointer(ListItem* _prev) {
	prev = _prev;
}


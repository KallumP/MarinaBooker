#include "Boat.h"

Boat::Boat() {
	length = -1;
	depth = -1;

	entryMonth = -1;
	leaveMonth = -1;

	linePosition = -1;
}

Boat::Boat(float _length, float _depth, int _entryMonth, int _leaveMonth) {
	length = _length;
	depth = _depth;

	entryMonth = _entryMonth;
	leaveMonth = _leaveMonth;

	linePosition = -1;
}

Boat::~Boat() {

}

int Boat::GetEnter() {
	return entryMonth;
}

void Boat::Leave(bool comeBack) {

}

void Boat::Return() {

}
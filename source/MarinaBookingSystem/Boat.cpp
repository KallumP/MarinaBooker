#include "Boat.h"

Boat::Boat() {
	length = -1;
	depth = -1;

	entryMonth = -1;
	leaveMonth = -1;

	linePosition = -1;
}

Boat::Boat(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name) {
	length = _length;
	depth = _depth;

	entryMonth = _entryMonth;
	leaveMonth = _leaveMonth;

	name = _name;

	linePosition = -1;
}

Boat::~Boat() {

}

int Boat::GetEnter() {
	return entryMonth;
}

std::string Boat::GetName() {
	return name;
}

void Boat::Leave(bool comeBack) {

}

void Boat::Return() {

}
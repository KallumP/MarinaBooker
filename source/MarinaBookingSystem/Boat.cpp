#include "Boat.h"

Boat::Boat() {
}

Boat::Boat(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name) {
	length = _length;
	depth = _depth;

	entryMonth = _entryMonth;
	leaveMonth = _leaveMonth;

	name = _name;
}

Boat::~Boat() {

}

int Boat::GetEnter() {
	return entryMonth;
}

int Boat::GetLeave() {
	return leaveMonth;
}

std::string Boat::GetName() {
	return name;
}
void Boat::SetName(std::string value) {
	 name = value;
}

int Boat::GetLength() {
	return length;
}


Narrow::Narrow(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name) : Boat(_length, _depth, _entryMonth, _leaveMonth, _name) {

}

Sailing::Sailing(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name) : Boat(_length, _depth, _entryMonth, _leaveMonth, _name) {

}

Motor::Motor(float _length, float _depth, int _entryMonth, int _leaveMonth, std::string _name) : Boat(_length, _depth, _entryMonth, _leaveMonth, _name) {

}
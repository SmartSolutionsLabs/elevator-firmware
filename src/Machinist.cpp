#include "Machinist.hpp"

Machinist::Machinist(const char * name, int taskCore) : Module(name, taskCore) {
}

Machinist::adviceFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;
}

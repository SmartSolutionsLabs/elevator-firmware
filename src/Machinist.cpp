#include "Machinist.hpp"

Machinist::Machinist(const char * name, int taskCore) : Module(name, taskCore) {
}

void Machinist::adviceFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;
}

void Machinist::connect(void * data) {
}

void Machinist::run(void* data) {
	while (1) {
		vTaskDelay(3 * this->iterationDelay);
	}
}

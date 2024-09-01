#include "Machinist.hpp"

Machinist::Machinist(const char * name, int taskCore) : Module(name, taskCore) {
}

void Machinist::handleArrivedFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;

	this->work();
}

void Machinist::handleDestinyFloor(unsigned int destinyFloor) {
	this->destinyFloor = destinyFloor;
}

void Machinist::connect(void * data) {
}

void Machinist::run(void* data) {
	while (1) {
		vTaskDelay(3 * this->iterationDelay);
	}
}

void Machinist::work() {
	static unsigned int currentFloor;

	if (this->floorStates[0] == true && this->floorStates[1] == false && this->floorStates[2] == false) {
		currentFloor = 0;
	}
	else if (this->floorStates[1] == true && this->floorStates[0] == false && this->floorStates[2] == false) {
		currentFloor = 1;
	}
	else if (this->floorStates[2] == true && this->floorStates[1] == false && this->floorStates[1] == false){
		currentFloor = 2;
	}
	else {
		// Error because I can't decide
		this->motor->off();
		return;
	}

	Serial.printf("Will move from %d to %d", currentFloor, (this->destinyFloor + 1));

	if(currentFloor < this->destinyFloor) {
		this->motor->up();
	}
	if(currentFloor > this->destinyFloor) {
		this->motor->down();
	}
	if(currentFloor == this->destinyFloor) {
		this->motor->off();
	}
}

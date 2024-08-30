#include "Elevator.hpp"

Elevator * elevator;

void setup(){
	elevator = new Elevator();
	elevator->initializeModulesPointerArray(8);
	elevator->beginSerialPort(Serial);
}

void loop() {
}

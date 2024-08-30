#include "Elevator.hpp"

Elevator * elevator;

void setup(){
	elevator = new Elevator();
	elevator->initializeModulesPointerArray(2);
	elevator->beginSerialPort(Serial);
}

void loop() {
}

#include "Elevator.hpp"

void Elevator::processMessage(unsigned char * message, size_t length, bool printable) {
	if (printable) {
		for (int i = 0; i < length; ++i) {
			Serial.print((char) message[i]);
		}
	}
	delete[] message;
	// Execute all instructions here
}

void Elevator::initializeModulesPointerArray(unsigned int quantity) {
	if (this->modulesPointer != nullptr) {
		while (this->modulesPointerQuantity) {
			delete this->modulesPointer[--this->modulesPointerQuantity];
		}
		delete[] this->modulesPointer;
	}

	this->modulesPointerQuantity = quantity;

	this->modulesPointer = new Module*[quantity];

	this->modulesPointer[0] = new Motor("Motor");
	this->modulesPointer[0]->start();

	// Pin number for sensor
	uint8_t pin;

	pin = 23;
	this->modulesPointer[1] = new Sensor("SensorFloor1");
	this->modulesPointer[1]->connect(&pin);

	pin = 16;
	this->modulesPointer[2] = new Sensor("SensorFloor2");
	this->modulesPointer[2]->connect(&pin);

	pin = 19;
	this->modulesPointer[3] = new Sensor("SensorFloor3");
	this->modulesPointer[3]->connect(&pin);

	this->modulesPointer[4] = new Joypad("jpd");
	this->modulesPointer[4]->start();

	this->modulesPointer[7] = new Machinist("machinist");

	// Passing machinist to all sensors
	static_cast<Sensor*>(this->modulesPointer[1])->setMachinist(static_cast<Machinist*>(this->modulesPointer[7]));
	static_cast<Sensor*>(this->modulesPointer[2])->setMachinist(static_cast<Machinist*>(this->modulesPointer[7]));
	static_cast<Sensor*>(this->modulesPointer[3])->setMachinist(static_cast<Machinist*>(this->modulesPointer[7]));

	static_cast<Sensor*>(this->modulesPointer[1])->setFloor(1);
	static_cast<Sensor*>(this->modulesPointer[2])->setFloor(2);
	static_cast<Sensor*>(this->modulesPointer[3])->setFloor(3);

	// starting sensors reading
	this->modulesPointer[1]->start();
	this->modulesPointer[2]->start();
	this->modulesPointer[3]->start();
}

Motor* Elevator::getMotor(){
	return static_cast<Motor*>(this->modulesPointer[0]);
}

Sensor* Elevator::getSensor(int index){
	return static_cast<Sensor*>(this->modulesPointer[index + 1]);
}

void Elevator::changingFloor(){
	this->isNotChangingFloor = false;
}

void Elevator::goToFloor(unsigned int floor) {
	static_cast<Machinist*>(this->modulesPointer[7])->setDestinyFloor(floor);
	static_cast<Machinist*>(this->modulesPointer[7])->work();
}

void Elevator::checkStatus(){
	this->getMotor()->showStatus();
}
	//isReady -> esta liberado para otra accion;
	//isMoving -> esta bloqueado porque se traslada de un piso a otro;
	//isWaiting -> esta esperando despues la llamada; (con timeout)

String Elevator::getState(){
	String statePrintable[5] ={"READY","MOVING","WAITING","ARRIVED","ERROR"};
	return statePrintable[state];
}

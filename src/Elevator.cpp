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

	this->modulesPointer[INDEX_MODULE_MOTOR] = new Motor("Motor");
	this->modulesPointer[INDEX_MODULE_MOTOR]->connect(nullptr);
	this->modulesPointer[INDEX_MODULE_MOTOR]->start();

	// Pin number for sensor
	uint8_t pin;

	pin = 23;
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1] = new Sensor("SensorFloor1");
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1]->connect(&pin);

	pin = 16;
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2] = new Sensor("SensorFloor2");
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2]->connect(&pin);

	pin = 19;
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3] = new Sensor("SensorFloor3");
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3]->connect(&pin);

	this->modulesPointer[INDEX_MODULE_JOYPAD] = new Joypad("jpd");
	this->modulesPointer[INDEX_MODULE_JOYPAD]->start();

	this->modulesPointer[INDEX_MODULE_MACHINIST] = new Machinist("machinist");

	// Passing machinist to all sensors
	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1])->setMachinist(static_cast<Machinist*>(this->modulesPointer[INDEX_MODULE_MACHINIST]));
	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2])->setMachinist(static_cast<Machinist*>(this->modulesPointer[INDEX_MODULE_MACHINIST]));
	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3])->setMachinist(static_cast<Machinist*>(this->modulesPointer[INDEX_MODULE_MACHINIST]));

	// Passing machinist to the joypad
	static_cast<Joypad*>(this->modulesPointer[INDEX_MODULE_JOYPAD])->setMachinist(static_cast<Machinist*>(this->modulesPointer[INDEX_MODULE_MACHINIST]));

	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1])->setFloor(1);
	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2])->setFloor(2);
	static_cast<Sensor*>(this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3])->setFloor(3);

	// starting sensors reading
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1]->start();
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2]->start();
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3]->start();
}

Motor* Elevator::getMotor(){
	return static_cast<Motor*>(this->modulesPointer[INDEX_MODULE_MOTOR]);
}

Sensor* Elevator::getSensor(int index){
	return static_cast<Sensor*>(this->modulesPointer[index + 1]);
}

void Elevator::goToFloor(unsigned int floor) {
	static_cast<Machinist*>(this->modulesPointer[INDEX_MODULE_MACHINIST])->handleTargetFloor(floor);
}

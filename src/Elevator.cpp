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
	this->modulesPointer[INDEX_MODULE_JOYPAD]->connect(nullptr);

	this->modulesPointer[INDEX_MODULE_MACHINIST] = new Machinist("machinist");

	// Passing machinist to all sensors
	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_1)->setMachinist(CAST_MODULE_POINTER(Machinist, INDEX_MODULE_MACHINIST));
	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_2)->setMachinist(CAST_MODULE_POINTER(Machinist, INDEX_MODULE_MACHINIST));
	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_3)->setMachinist(CAST_MODULE_POINTER(Machinist, INDEX_MODULE_MACHINIST));

	// Passing machinist to the joypad
	CAST_MODULE_POINTER(Joypad, INDEX_MODULE_JOYPAD)->setMachinist(CAST_MODULE_POINTER(Machinist, INDEX_MODULE_MACHINIST));

	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_1)->setFloor(1);
	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_2)->setFloor(2);
	CAST_MODULE_POINTER(Sensor, INDEX_MODULE_SENSOR_FLOOR_3)->setFloor(3);

	// starting sensors reading
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_1]->start();
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_2]->start();
	this->modulesPointer[INDEX_MODULE_SENSOR_FLOOR_3]->start();

	// starting buttons reading
	this->modulesPointer[INDEX_MODULE_JOYPAD]->start();
}

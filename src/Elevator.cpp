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

	pin = 16;
	this->modulesPointer[1] = new Sensor("SensorFloor1");
	this->modulesPointer[1]->connect(&pin);

	pin = 23;
	this->modulesPointer[2] = new Sensor("SensorFloor2");
	this->modulesPointer[2]->connect(&pin);

	pin = 19;
	this->modulesPointer[3] = new Sensor("SensorFloor3");
	this->modulesPointer[3]->connect(&pin);

	this->modulesPointer[4] = new Button("Button1");
	this->modulesPointer[4]->start();
	this->getButton(0)->setPIN(17);

	this->modulesPointer[5] = new Button("Button2");
	this->modulesPointer[5]->start();
	this->getButton(1)->setPIN(5);

	 this->modulesPointer[6] = new Button("Button3");
	this->modulesPointer[6]->start();
	this->getButton(2)->setPIN(18);

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

Button* Elevator::getButton(int index){
	return static_cast<Button*>(this->modulesPointer[index + 4]);
}

void Elevator::changingFloor(){
	this->isNotChangingFloor = false;
}

void Elevator::setDestinyFloor(unsigned int destinyfloor){
	this->destinyFloor = destinyfloor;
}

void Elevator::goToFloor(unsigned int floor){
	this->destinyFloor = floor;
	Serial.println("mandando al piso" + String(floor+1));
	if(this->currentFloor < floor){
		Serial.println("motor trying go up");
		this->getMotor()->up();
		Serial.println("motor go up");
	}
	if(this->currentFloor > floor){
		Serial.println("motor trying go down");
		this->getMotor()->down();
		Serial.println("motor go down");
	}
	if(this->currentFloor == floor){
		Serial.println("motor stop...");
		this->getMotor()->off();
		Serial.println("motor stop");
	}
}

void Elevator::checkFloor(){
	if(this->getSensor(0)->getValue()==true && this->getSensor(1)->getValue()==false && this->getSensor(2)->getValue()==false){
		this->currentFloor = 0;
	}
	else if(this->getSensor(0)->getValue()==false && this->getSensor(1)->getValue()==true && this->getSensor(2)->getValue()==false){
		this->currentFloor = 1;
	}
	else if(this->getSensor(0)->getValue()==false && this->getSensor(1)->getValue()==false && this->getSensor(2)->getValue()==true){
		this->currentFloor = 2;
	}
	else{
		//error!
	}

	if(this->currentFloor == this->destinyFloor){
		//this->state = ARRIVED;
		this->getMotor()->off();
	}
	else{
		//this->getSensor(this->currentFloor)->setValue(false);
	}

}

void Elevator::checkControl(){
	if(state == READY){
		if(this->getButton(0)->getValue()){
			this->goToFloor(0);
		}
		else if(this->getButton(1)->getValue()){
			this->goToFloor(1);
		}
		else if(this->getButton(2)->getValue()){
			this->goToFloor(2);
		}
	}
}

void Elevator::checkStatus(){
	this->getMotor()->showStatus();
}
	//isReady -> esta liberado para otra accion;
	//isMoving -> esta bloqueado porque se traslada de un piso a otro;
	//isWaiting -> esta esperando despues la llamada; (con timeout)
unsigned int Elevator::getCurrentFloor(){
	return this->currentFloor;
}

unsigned int Elevator::getDestinyFloor(){
	return this->destinyFloor;
}

String Elevator::getState(){
	String statePrintable[5] ={"READY","MOVING","WAITING","ARRIVED","ERROR"};
	return statePrintable[state];
}

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

    this->modulesPointer[1] = new Sensor("SensorFloor1");
    this->modulesPointer[1]->start();

    this->modulesPointer[2] = new Sensor("SensorFloor2");
    this->modulesPointer[2]->start();
    
    this->modulesPointer[3] = new Sensor("SensorFloor3");
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

void Elevator::goToFloor(unsigned int floor){
    if(READY){
        if(this->currentFloor < floor){
            this->getMotor()->up();
        }
        if(this->currentFloor > floor){
            this->getMotor()->down();
        }
        if(this->currentFloor == floor){
            this->getMotor()->stop();
        }
    }
}

void Elevator::checkFloor(){

    if(this->getSensor(0)->getValue()==true && this->getSensor(1)->getValue()==false && this->getSensor(1)->getValue()==false){
        this->currentFloor = 0;
    }
    else if(this->getSensor(0)->getValue()==false && this->getSensor(1)->getValue()==true && this->getSensor(1)->getValue()==false){
        this->currentFloor = 1;
    }
    else if(this->getSensor(0)->getValue()==false && this->getSensor(1)->getValue()==false && this->getSensor(1)->getValue()==true){
        this->currentFloor = 2;
    }
    else{
        //error!
        return;
    }

    if(this->currentFloor == this->destinyFloor){
        this->state = ARRIVED;
        this->getMotor()->off();
    }
    else{
        this->getSensor(this->currentFloor)->setValue(false);
    }

}

void Elevator::checkControl(){
    
}
    //isReady -> esta liberado para otra accion;
    //isMoving -> esta bloqueado porque se traslada de un piso a otro;
    //isWaiting -> esta esperando despues la llamada; (con timeout)
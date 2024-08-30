#include "Elevator.hpp"

Elevator * elevator; 

void IRAM_ATTR SensorFloor1() {
    elevator->getSensor(0)->setValue(true);
    elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}

void IRAM_ATTR SensorFloor2() {
    elevator->getSensor(1)->setValue(true);
    elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}

void IRAM_ATTR SensorFloor3() {
    elevator->getSensor(2)->setValue(true);
    elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}


void IRAM_ATTR Button1() {
    elevator->goToFloor(1);
}



void setup(){
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(19), SensorFloor1, FALLING); // Configure the interrupt
    attachInterrupt(digitalPinToInterrupt(17), Button1, FALLING); // Configure the interrupt

    elevator = new Elevator();
	elevator->initializeModulesPointerArray(2);


	//elevator->beginSerialPort(Serial);

}

void loop(){
}
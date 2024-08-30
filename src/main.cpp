#include "Elevator.hpp"

Elevator * elevator;

/*
void IRAM_ATTR SensorFloor1() {
    elevator->getSensor(0)->setValue(true);
    digitalWrite(12,LOW);
    //elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}

void IRAM_ATTR SensorFloor2() {
    elevator->getSensor(1)->setValue(true);
    //elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}

void IRAM_ATTR SensorFloor3() {
    elevator->getSensor(2)->setValue(true);
    //elevator->checkFloor(); // s1 = on . s3 = on , s2 = off
}

void IRAM_ATTR interruptButton1() {
    elevator->setDestinyFloor(1);
}

void IRAM_ATTR interruptButton2() {
    elevator->setDestinyFloor(2);
}

void IRAM_ATTR interruptButton3() {
    elevator->setDestinyFloor(3);
}
*/

void setup(){
    Serial.begin(115200);
    pinMode(12,OUTPUT);
    digitalWrite(12,HIGH);
    /*
    attachInterrupt(digitalPinToInterrupt(19), SensorFloor1, RISING); // Configure the interrupt
    attachInterrupt(digitalPinToInterrupt(23), SensorFloor2, RISING); // Configure the interrupt
    attachInterrupt(digitalPinToInterrupt(16), SensorFloor3, RISING); // Configure the interrupt

    attachInterrupt(digitalPinToInterrupt(17), interruptButton1, RISING); // Configure the interrupt
    attachInterrupt(digitalPinToInterrupt(5),  interruptButton2, RISING); // Configure the interrupt
    attachInterrupt(digitalPinToInterrupt(18), interruptButton3, RISING); // Configure the interrupt
    */
    elevator = new Elevator();
	elevator->initializeModulesPointerArray(2);

	//elevator->beginSerialPort(Serial);
}

 unsigned long loopTimer = 0;
void loop(){
    if(millis() -loopTimer > 1500){
        loopTimer = millis();
        Serial.println("\t STATE OF ELEVATOR   : " + String(elevator->getState()));
        Serial.println("floor   : " + String(elevator->getCurrentFloor()+1));
        Serial.println("destiny : " + String(elevator->getDestinyFloor()+1));
        Serial.println("Motor State : " + String(elevator->getMotor()->getState()));
        Serial.println("Sensor 1 : " + String(elevator->getSensor(0)->getValue()));
        Serial.println("Sensor 2 : " + String(elevator->getSensor(1)->getValue()));
        Serial.println("Sensor 3 : " + String(elevator->getSensor(2)->getValue()));

        Serial.println("Button 1 : " + String(elevator->getButton(0)->getValue()));
        Serial.println("Button 2 : " + String(elevator->getButton(1)->getValue()));
        Serial.println("Button 3 : " + String(elevator->getButton(2)->getValue()));

    }
    elevator->checkFloor();
    elevator->checkControl();
    delay(10);
}

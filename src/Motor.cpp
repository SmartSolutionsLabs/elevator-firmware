#include "Motor.hpp"

Motor::Motor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Motor::connect(void * data) {
	pinMode(12,OUTPUT);
	pinMode(14,OUTPUT);
	digitalWrite(12,LOW);
	digitalWrite(14,LOW);
}

void Motor::run(void* data) {
	while (1) {
		vTaskDelay(this->iterationDelay);
		Serial.print("motor iter\n");
	}
}

void Motor::off(){
	digitalWrite(12,LOW);
	digitalWrite(14,LOW);
}

void Motor::up(){
	digitalWrite(12,HIGH);
	digitalWrite(14,LOW);
}

void Motor::down(){
	digitalWrite(12,HIGH);
	digitalWrite(14,HIGH);
}
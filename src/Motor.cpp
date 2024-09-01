#include "Motor.hpp"

Motor::Motor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Motor::connect(void * data) {
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(14, OUTPUT);
	digitalWrite(12, HIGH);
	digitalWrite(13, HIGH);
	digitalWrite(14, HIGH);
}

void Motor::run(void* data) {
	while (1) {
		vTaskDelay(this->iterationDelay);
	}
}

void Motor::off() {
	digitalWrite(12, HIGH);
	digitalWrite(14, HIGH);
	this->state = OFF;
}

void Motor::up() {
	digitalWrite(12, LOW);
	digitalWrite(14, LOW);
	this->state = UP;
}

void Motor::down() {
	digitalWrite(12, LOW);
	digitalWrite(14, HIGH);
	this->state = DOWN;
}

void Motor::showStatus() {
	//Serial.println(String(name) + "\n Status : " + String(state));
}

unsigned int Motor::getState() {
	return this->state;
}

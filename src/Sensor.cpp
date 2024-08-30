#include "Sensor.hpp"

Sensor::Sensor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Sensor::connect(void * data) {

}

void Sensor::run(void* data) {
	unsigned long timer = millis();
	while (1) {
		if(digitalRead(this->PIN) == false){ // pushed
			this->currentValue = false;
		}
		else{
			this->currentValue = true;
		}

		if(this->lastValue == true && this->currentValue == false){
			this->value = true;
			this->lastValue = this->currentValue;
		}
		else if(this->lastValue == false && this-> currentValue == true){
			this->lastValue = this->currentValue;
			this->value = false;
		}
		vTaskDelay(10);
	}
}

void Sensor::setValue(bool value){
	this->value = value;
}

void Sensor::setPIN(uint8_t pin){
	this->PIN = pin;
	pinMode(this->PIN , INPUT);
}

#include "Sensor.hpp"

Sensor::Sensor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Sensor::connect(void * data) {
	this->pin = * (uint8_t *) data;
	pinMode(this->pin , INPUT);
}

void Sensor::run(void* data) {
	unsigned long timer = millis();
	while (1) {
		if(digitalRead(this->pin) == false){ // pushed
			this->currentValue = false;
		}
		else{
			this->currentValue = true;
		}

		if(this->lastValue == true && this->currentValue == false){
			this->value = true;
			this->lastValue = this->currentValue;

			this->machinist->adviceFloor(this->floorIndex, this->value);
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

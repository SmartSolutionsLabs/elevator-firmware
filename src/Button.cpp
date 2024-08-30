#include "Button.hpp"

Button::Button(const char * name, int taskCore) : Module(name, taskCore) {
}

void Button::connect(void * data) {
}

void Button::run(void* data) {
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

void Button::setValue(bool value){
	this->value = value;
}

void Button::setPIN(uint8_t pin){
	this->PIN = pin;
	pinMode(this->PIN , INPUT);
}
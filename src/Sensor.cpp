#include "Sensor.hpp"

Sensor::Sensor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Sensor::connect(void * data) {
	this->pin = * (uint8_t *) data;
	pinMode(this->pin , INPUT);
}

void Sensor::run(void* data) {
	this->iterationDelay = 10 / portTICK_PERIOD_MS;

	while (1) {
		this->reading = digitalRead(this->pin); // LOW is pressed

		if (this->reading != this->lastButtonState) {
			this->lastDebounceTime = millis();  // Reset debouncer
		}
		if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
			if (this->reading != this->buttonState) {
				this->buttonState = this->reading;
				if (this->buttonState == LOW) {  // Button pressed
					this->machinist->handleArrivedFloor(this->floorIndex, this->buttonState);
					Serial.printf("Floor %d detected\n", this->floorIndex);
				}
			}
		}
		this->lastButtonState = this->reading;

		// A little delay to avoid many reads
		vTaskDelay(this->iterationDelay);
	}
}

bool Sensor::getValue(){
	bool sensorState = !(digitalRead(this->pin));
	return sensorState;
}
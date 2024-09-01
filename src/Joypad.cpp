#include "Joypad.hpp"

Joypad::Joypad(const char * name, int taskCore) : Module(name, taskCore) {
	this->floorButtons[0].pin = 17;
	this->floorButtons[1].pin = 5;
	this->floorButtons[2].pin = 18;

	this->iterationDelay = 10 / portTICK_PERIOD_MS;
}

void Joypad::connect(void * data) {
	pinMode(this->floorButtons[0].pin, INPUT_PULLUP);
	pinMode(this->floorButtons[1].pin, INPUT_PULLUP);
	pinMode(this->floorButtons[2].pin, INPUT_PULLUP);
}

void Joypad::run(void* data) {
	// floor buttons quantity
	unsigned int i = (sizeof(this->floorButtons) / sizeof(*this->floorButtons));

	while (1) {
		// Verify floor button state
		while (i > 0) {
			--i;
			this->floorButtons[i].reading = digitalRead(this->floorButtons[i].pin);
			if (this->floorButtons[i].reading != this->floorButtons[i].lastButtonState) {
				this->floorButtons[i].lastDebounceTime = millis();  // Reset debouncer
			}
			if ((millis() - this->floorButtons[i].lastDebounceTime) > this->debounceDelay) {
				if (this->floorButtons[i].reading != this->floorButtons[i].buttonState) {
					this->floorButtons[i].buttonState = this->floorButtons[i].reading;
					if (this->floorButtons[i].buttonState == LOW) {  // Button pressed
						Serial.printf("Btn %d pressed\n", i);
					}
				}
			}
			this->floorButtons[i].lastButtonState = this->floorButtons[i].reading;
		}

		// A little delay to avoid many reads
		vTaskDelay(this->iterationDelay);
	}
}

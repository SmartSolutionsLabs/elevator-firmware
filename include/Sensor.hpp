#ifndef INC_SENSOR
#define INC_SENSOR

#include <Module.hpp>

#include "Machinist.hpp"

class Sensor : public Module {
	private:
		bool buttonState = 0;
		bool lastButtonState = 0;
		bool reading;
		unsigned long lastDebounceTime = 0;
		const unsigned long debounceDelay = 50; // debounce time in milliseconds
		uint8_t pin;
		unsigned int floorIndex;

		Machinist * machinist;

	public:
		Sensor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		bool getValue() const {
			return buttonState;
		}

		void setFloor(unsigned int floor) {
			floorIndex = floor;
		}

		void setMachinist(Machinist * newMachinist) {
			machinist = newMachinist;
		}

		bool getValue();
};

#endif

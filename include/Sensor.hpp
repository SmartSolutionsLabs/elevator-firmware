#ifndef INC_SENSOR
#define INC_SENSOR

#include <Module.hpp>

class Sensor : public Module {
	private:
		bool value = 0;
		bool lastValue = 0;
		bool currentValue = 0;
		uint8_t PIN ;
	public:
		Sensor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		bool getValue() const {
			return value;
		}

		void setValue(bool value);
		void setPIN(uint8_t pin);
};

#endif

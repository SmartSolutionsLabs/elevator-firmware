#ifndef INC_BUTTON
#define INC_BUTTON

#include <Module.hpp>

class Button : public Module {
	private:
		bool value = 0;
		bool lastValue = 0;
		bool currentValue = 0;
		uint8_t PIN ;
	public:
		Button(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		bool getValue() const {
			return value;
		}

		void setValue(bool value);
		void setPIN(uint8_t pin);
};

#endif

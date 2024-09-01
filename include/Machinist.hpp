#ifndef INC_MACHINIST
#define INC_MACHINIST

#include <Module.hpp>

#include "Motor.hpp"

class Machinist : public Module {
	private:
		/**
		 * Where basket must go.
		 */
		unsigned int destinyFloor;

		bool floorStates[3];

		Motor * motor;

	public:
		Machinist(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		/**
		 * Performs movement of basket.
		 */
		void work();

		/**
		 * Modify values in floors array.
		 */
		void handleArrivedFloor(unsigned int floorIndex, bool value);

		void setDestinyFloor(unsigned int destinyFloor) {
			destinyFloor = destinyFloor;
		}

		void setMotor(Motor * motor) {
			motor = motor;
		}
};

#endif

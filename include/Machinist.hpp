#ifndef INC_MACHINIST
#define INC_MACHINIST

#include <Module.hpp>

#include "Motor.hpp"

enum Work {
	READY, // accepting instructions from anyone and executes "inmediately"
	MOVING_DOWN, // ascending
	MOVING_UP, // descending
	WAITING, // basket arrived from another floor to current floor
	ARRIVED, // work completed
	LOST // bewildered, disconcerted to take decisions
};

class Machinist : public Module {
	private:
		Work state;

		/**
		 * Where basket must go.
		 */
		unsigned int targetFloor;

		bool floorStates[3];

		Motor * motor;

		/**
		 * Performs movement of basket.
		 */
		void work();

		/**
		 * It's the countdown hand.
		 */
		esp_timer_handle_t countdownHandTimer = nullptr;

		std::function<void()> privateAction;

	public:
		Machinist(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		/**
		 * Modify values in floors array.
		 */
		void handleArrivedFloor(unsigned int floorIndex, bool value);

		/**
		 * Catch calling from buttons.
		 */
		void handleTargetFloor(unsigned int targetFloor);

		void setMotor(Motor * motor) {
			motor = motor;
		}
};

#endif

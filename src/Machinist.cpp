#include "Machinist.hpp"

Machinist::Machinist(const char * name, int taskCore) : Module(name, taskCore), state(READY) {
	// defining lambda to call the private work
	this->privateAction = [this]() {
		// Since timer was execute then free its resources
		if (this->countdownHandTimer) {
			esp_timer_delete(this->countdownHandTimer);
			this->countdownHandTimer = nullptr;
		}

		this->work();
	};
}

void Machinist::handleArrivedFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;

	this->work();
}

void Machinist::handleTargetFloor(unsigned int targetFloor) {
	this->targetFloor = targetFloor;

	if(this->countdownHandTimer == nullptr) {
		static const esp_timer_create_args_t countdown_timer_args = {
				.callback = [](void* arg) {
					auto* lambda = static_cast<std::function<void()>*>(arg);
					(*lambda)(); // Execute lambda
				},
				.arg = &this->privateAction,
				.dispatch_method = ESP_TIMER_TASK,
				.name = "machinist-countdown"
		};
		esp_timer_create(&countdown_timer_args, &this->countdownHandTimer);
		esp_timer_start_once(this->countdownHandTimer, 5000000); // One shot after 5 seconds
	}
}

void Machinist::connect(void * data) {
}

void Machinist::run(void* data) {
	while (1) {
		vTaskDelay(3 * this->iterationDelay);
	}
}

void Machinist::work() {
	Serial.print("I will work...\n");
	static unsigned int currentFloor;

	if (this->floorStates[0] == true && this->floorStates[1] == false && this->floorStates[2] == false) {
		currentFloor = 0;
	}
	else if (this->floorStates[1] == true && this->floorStates[0] == false && this->floorStates[2] == false) {
		currentFloor = 1;
	}
	else if (this->floorStates[2] == true && this->floorStates[1] == false && this->floorStates[1] == false){
		currentFloor = 2;
	}
	else {
		// Error because I can't decide
		this->motor->off();
		this->state = LOST;
		return;
	}

	Serial.printf("Will move from %d to %d", currentFloor, (this->targetFloor + 1));

	// Turn off because we arrived
	if(currentFloor == this->targetFloor) {
		// I hope everything is right
		this->motor->off();
		this->state = ARRIVED;

		return;
	}

	if(currentFloor < this->targetFloor) {
		this->motor->up();
		this->state = GOING_UP;
		return;
	}

	if(currentFloor > this->targetFloor) {
		this->motor->down();
		this->state = GOING_DOWN;
		return;
	}
}

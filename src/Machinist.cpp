#include "Machinist.hpp"

void IRAM_ATTR interruptCountdownHand(void* arg) {
	Machinist * machinist = (Machinist *) arg;
}

Machinist::Machinist(const char * name, int taskCore) : Module(name, taskCore) {
}

void Machinist::handleArrivedFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;

	this->work();
}

void Machinist::handleDestinyFloor(unsigned int destinyFloor) {
	this->destinyFloor = destinyFloor;

	// defining lambda to use the private method
	auto privateAction = [this]() {
		this->work();
	};

	if(this->countdownHandTimer == nullptr) {
		static const esp_timer_create_args_t countdown_timer_args = {
				.callback = [](void* arg) {
					auto* lambda = static_cast<decltype(privateAction)*>(arg);
					(*lambda)(); // Execute lambda
				},
				.arg = (void *) this,
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
		return;
	}

	Serial.printf("Will move from %d to %d", currentFloor, (this->destinyFloor + 1));

	if(currentFloor < this->destinyFloor) {
		this->motor->up();
	}
	if(currentFloor > this->destinyFloor) {
		this->motor->down();
	}
	if(currentFloor == this->destinyFloor) {
		this->motor->off();
	}
}

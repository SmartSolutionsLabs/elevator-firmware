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

Machinist::~Machinist() {
	if (this->countdownHandTimer) {
		esp_timer_stop(this->countdownHandTimer);
	}

	if (this->countdownHandTimer) {
		esp_timer_delete(this->countdownHandTimer);
	}
}

void Machinist::handleArrivedFloor(unsigned int floorIndex, bool value) {
	this->floorStates[floorIndex - 1] = value;

	this->work();
}

void Machinist::handleTargetFloor(unsigned int targetFloor) {
	if (targetFloor == 0 || targetFloor > this->upperLimit) {
		Serial.print("target floor out of bound\n");
		return;
	}

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

void Machinist::work(){
	Serial.println("State : " + String(this->state));
	Serial.print("I will work...\n");

	if(this->state == HOME){
		Serial.println("I am making Home");
		this->state = READY;
		return;
	}

	if (this->floorStates[0] == true && this->floorStates[1] == false && this->floorStates[2] == false) {
		currentFloor = 1;
		Serial.println("floor set 1");
	}
	else if (this->floorStates[1] == true && this->floorStates[0] == false && this->floorStates[2] == false) {
		currentFloor = 2;
		Serial.println("floor set 2");
	}
	else if (this->floorStates[2] == true && this->floorStates[1] == false && this->floorStates[1] == false){
		currentFloor = 3;
		Serial.println("floor set 3");
	}
	else {
		// Error because I can't decide
		this->motor->off();
		Serial.println("floor lost");
		this->state = LOST;
		return;
	}

	Serial.printf("Will move from %d to %d", (this->currentFloor), (this->targetFloor));

	// Turn off because we arrived
	if(this->currentFloor == this->targetFloor) {
		// I hope everything is right
		this->motor->off();
		this->state = ARRIVED;

		return;
	}

	if(this->currentFloor < this->targetFloor) {
		this->motor->up();
		this->state = GOING_UP;
		return;
	}

	if(this->currentFloor > this->targetFloor) {
		this->motor->down();
		this->state = GOING_DOWN;
		return;
	}
}

void Machinist::setFloorStates(bool floor1 , bool floor2, bool floor3){
	this->floorStates[0] = floor1;
	this->floorStates[1] = floor2;
	this->floorStates[2] = floor3;
	this->state = HOME;

	if (this->floorStates[0] == true && this->floorStates[1] == false && this->floorStates[2] == false) {
		this->currentFloor = 1;
		Serial.println("floor set 1");
	}
	else if (this->floorStates[1] == true && this->floorStates[0] == false && this->floorStates[2] == false) {
		this->currentFloor = 2;
		Serial.println("floor set 2");
	}
	else if (this->floorStates[2] == true && this->floorStates[1] == false && this->floorStates[1] == false){
		this->currentFloor = 3;
		Serial.println("floor set 3");
	}
}
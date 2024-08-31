#ifndef _INC_ELEVATOR_
#define _INC_ELEVATOR_

#include <Application.hpp>
#include "Sensor.hpp"
#include "Button.hpp"
#include "Motor.hpp"
#include "Machinist.hpp"


class Elevator : public Application {
	public:
		void processMessage(unsigned char * message, size_t length, bool printable);
		void initializeModulesPointerArray(unsigned int quantity) override;
		Motor* getMotor();
		Sensor* getSensor(int index);
		Button* getButton(int index);

		unsigned int startFloor = 1;
		bool isNotChangingFloor = true;

		void changingFloor();
		void goToFloor(unsigned int floor);
		void checkFloor(); //cambia estados
		void checkControl(); // VERIFICA SI SE PUEDE LLAMAR EL ASCENSOR DESDE OTRO PISO
		void setHome(); // INICIALIZA EL ASCENSOR A UN LUGAR SEGURO
		void checkStatus();
		enum State{ READY,
					MOVING,
					WAITING,
					ARRIVED,
					ERROR
		} state = READY;
		String getState();
};

#endif

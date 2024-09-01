#ifndef _INC_ELEVATOR_
#define _INC_ELEVATOR_

#include <Application.hpp>
#include "Sensor.hpp"
#include "Motor.hpp"
#include "Machinist.hpp"
#include "Joypad.hpp"

#define INDEX_MODULE_MOTOR 0

#define INDEX_MODULE_SENSOR_FLOOR_1 (INDEX_MODULE_MOTOR + 1)
#define INDEX_MODULE_SENSOR_FLOOR_2 (INDEX_MODULE_SENSOR_FLOOR_1 + 1)
#define INDEX_MODULE_SENSOR_FLOOR_3 (INDEX_MODULE_SENSOR_FLOOR_2 + 1)

#define INDEX_MODULE_JOYPAD (INDEX_MODULE_SENSOR_FLOOR_3 + 1)

#define INDEX_MODULE_MACHINIST (INDEX_MODULE_JOYPAD + 1)

class Elevator : public Application {
	public:
		void processMessage(unsigned char * message, size_t length, bool printable);
		void initializeModulesPointerArray(unsigned int quantity) override;
		Motor* getMotor();
		Sensor* getSensor(int index);

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

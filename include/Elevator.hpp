#ifndef _INC_ELEVATOR_
#define _INC_ELEVATOR_

#include <Application.hpp>
#include "Sensor.hpp"
#include "Motor.hpp"


class Elevator : public Application {
	public:
		void processMessage(unsigned char * message, size_t length, bool printable);
		void initializeModulesPointerArray(unsigned int quantity) override;
        Motor* getMotor();
        Sensor* getSensor(int index);

        unsigned int currentFloor = 1;
        unsigned int destinyFloor = 1;
        unsigned int startFloor = 1;
        bool isNotChangingFloor = true;

        void changingFloor();
        void goToFloor(unsigned int floor);
        void checkFloor(); //cambia estados
        void checkControl(); // VERIFICA SI SE PUEDE LLAMAR EL ASCENSOR DESDE OTRO PISO
        void setHome(); // INICIALIZA EL ASCENSOR A UN LUGAR SEGURO

        enum State{ READY,
                    MOVING,
                    WAITING,
                    ARRIVED,
                    ERROR
        } state;
};

#endif

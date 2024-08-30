#ifndef INC_MACHINIST
#define INC_MACHINIST

#include <Module.hpp>

class Machinist : public Module {
	private:
		/**
		 * Where basket must go.
		 */
		unsigned int destinyFloor;

		bool floorStates[3];
	public:
		Machinist(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		/**
		 * Modify values in floors array.
		 */
		void adviceFloor(unsigned int floorIndex, bool value);
};

#endif

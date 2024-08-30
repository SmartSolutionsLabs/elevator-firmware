#ifndef INC_MACHINIST
#define INC_MACHINIST

#include <Module.hpp>

class Machinist : public Module {
	private:
		bool floorStates[3];
	public:
		Machinist(const char * name, int taskCore = 1);

		/**
		 * Modify values in floors array.
		 */
		void adviceFloor(unsigned int floorIndex, bool value);
};

#endif

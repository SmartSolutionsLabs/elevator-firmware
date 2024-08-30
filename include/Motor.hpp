#ifndef INC_MOTOR
#define INC_MOTOR

#include <Module.hpp>

class Motor : public Module {
	private:
		bool running = false;
		bool PIN;
	public:
		Motor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		void setRunning(bool running) {
			running = running;
		}

		bool isRunning() const {
			return running;
		}

		void off();

		void up();

		void down();

		void showStatus();

		enum{
				OFF,
				UP,
				DOWN
		}state = OFF;

		unsigned int getState();
};

#endif

#include "Timer.h"

class TimeManagement {

	TimeManagement();

	void Start();
	void Stop();
	

public:

	static void Pause();
	static void Resume();

	static float GameTimer();
	static float RealTimer();

public:


	static bool paused;
	static bool started;

	static float timeScale;
	static float dt;

	static Timer gameTimer;
	static Timer realTimer;

};

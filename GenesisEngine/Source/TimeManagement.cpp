#include "TimeManagement.h"
#include "Application.h"

Timer TimeManagement::realTimer;
Timer TimeManagement::gameTimer;

bool TimeManagement::paused = false;
bool TimeManagement::started = false;
float TimeManagement::timeScale = 1;
float TimeManagement::dt = 0;

void TimeManagement::Start()
{
	paused = false;
	started = false;
	timeScale = 1;
	dt = 0;

	gameTimer.Start();
	realTimer.Start();
}

TimeManagement::TimeManagement()
{
	timeScale = 1.0f;
	paused = false;
}

void TimeManagement::Stop()
{
	paused = false;
	started = false;
	gameTimer.Stop();
}

void TimeManagement::Pause()
{
	paused = true;
	gameTimer.Stop();
}

void TimeManagement::Resume()
{
	paused = false;
	gameTimer.Resume();
}

float TimeManagement::GameTimer() {

	if (App->game_started != false) {
		return gameTimer.Read() / 1000;
	}
	else {
		return 0;
	}
}

float TimeManagement::RealTimer() {
	return realTimer.ReadSec();
}

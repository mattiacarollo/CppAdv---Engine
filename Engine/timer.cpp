#include "timer.h"

using namespace utility;

Timer::Timer()
	: mStartTimel(0)
{}

void Timer::start()
{
	mStartTimel = GetTickCount();
}

DWORD Timer::elapsedMSec()
{
	return GetTickCount() - mStartTimel;
}

float Timer::elapsedSecF()
{
	return elapsedMSec() / 1000.0f;
}

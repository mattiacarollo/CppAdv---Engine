#pragma once

#include <Windows.h>

namespace utility
{
	class Timer
	{
	public:
		Timer();

		void start();
		DWORD elapsedMSec();
		float elapsedSecF();

	private:
		DWORD mStartTimel;
	};
}

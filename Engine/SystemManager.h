#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "InputManager.h"

class SystemManager
{

public:
	SystemManager(); 
	SystemManager(const SystemManager&); 
	~SystemManager(); 

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM); 

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCSTR m_applicationName; 
	HINSTANCE m_hinstance; 
	HWND m_hwnd; 
	InputManager* m_Input;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
static SystemManager* ApplicationHandle = 0; 

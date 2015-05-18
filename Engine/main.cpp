#include <Windows.h>
#include "SystemManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Application app(hInstance, nCmdShow);
	//app.setWindowTitle(L"C++ Advanced Engine");
	//app.setWindowSize(640, 480);

	//return app.run();

	bool result;
	SystemManager* System; 
	System = new SystemManager; 
	if (!System) { return 0; }
	result = System->Initialize();
	if (result){ System->Run();	}	
	System->Shutdown(); 
	delete System;
	System = 0; 

	return 0;
}
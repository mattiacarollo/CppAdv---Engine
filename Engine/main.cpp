#include <Windows.h>

#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app(hInstance, nCmdShow);
	app.setWindowTitle(L"C++ Advanced Engine");
	app.setWindowSize(640, 480);

	return app.run();
}
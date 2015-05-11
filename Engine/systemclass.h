////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN

//////////////
// INCLUDES //
//////////////
#include <windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "graphicsclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass(); // Costrutt.
	SystemClass(const SystemClass&); // Costrutt. copia
	~SystemClass(); //Distr.

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM); // gestisce mesaggi sistema

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName; // is a 32-bit pointer to a constant string of 16-bit
	HINSTANCE m_hinstance; //A handle to an instance. This is the base address of the module in memory
	HWND m_hwnd; // l'handle di una finestra

	InputClass* m_Input; // Oggetto Input 
	GraphicsClass* m_Graphics; // Oggetto Graphic
};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //Gestisce messaggi sistema

/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0; // puntatore utilizzato da handler


#endif
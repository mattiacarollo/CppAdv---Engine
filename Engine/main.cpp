////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System; //Creiamo oggetto SystemClass
	bool result; //Boolean per vedere se l'oggetto è stato creato bene


	// Create the system object.
	System = new SystemClass; // Creiamo oggetto
	if (!System) // Controllo validità puntatore
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize(); // Inizializziamo l'oggetto System chiamando Inizialize
	if (result)
	{
		System->Run(); // Se inizializzato correttamente chiamiamo run
	}

	// Shutdown and release the system object.
	System->Shutdown(); // Quando esce dal loop run, Shutdown oggetto
	delete System; // Cancelliamo puntatore
	System = 0; // Impostiamo a valore nullo

	return 0;
}
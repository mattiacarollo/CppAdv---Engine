#pragma once

#include "sampleProgram.h"

class Application : public mcg::SampleProgram
{
public:
	Application(HINSTANCE hInstance, int nCmdShow);

	HRESULT initializeResources();
	void cleanResouces();

	void prerender();
	void render();
	void postrender();

private:
	
};

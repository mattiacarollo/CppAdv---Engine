#pragma once

#include <tchar.h>
#include <Windows.h>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "Vector3.h"
#include "Physic.h"
#include "RigidBody.h"
#include "SphereCollider.h"

Vector3 SphereInertia(float mass, float radius)
{
	//inertia moment of full sphere (I = 2/5 * (m*r^2))
	float inertia = 2 * mass*radius*radius / 5;
	return Vector3(inertia, inertia, inertia);
}

Physic p;
RigidBody* rBSphere0 = new RigidBody(Vector3(-4.0f, -4.0f, 1.0f), 0, 100.0f, SphereInertia(100.0f, 5.0f));
RigidBody* rBSphere1 = new RigidBody(Vector3(4.0f, 0.0f, 1.0f), 0, 100.0f, SphereInertia(100.0f, 5.0f));

float DT = 0.005f;
double TempoTotale = 0;

void DisegnaSfera(float X, float Y, float Z, float R);
void DisegnaPianoXZ(float QuotaZ);
static GLfloat rosso[] = { 2.0f, 0.1f, 0.1f, 1.0f };
static GLfloat verde2[] = { 0.4f, 1.0f, 0.4f, 1.0f };
static GLfloat blu[] = { 0.4f, 0.4f, 1.0f, 1.0f };
static GLfloat bianco[] = { 1.0f, 1.0f, 1.0f, 1.0f };
void DisegnaPianoXZ(float Y)
{
	int i;
	float Dim = 20;

	glMaterialfv(GL_FRONT, GL_AMBIENT, verde2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, verde2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bianco);
	glMateriali(GL_FRONT, GL_SHININESS, 16);

	glBegin(GL_LINES);
	glNormal3f(0, 1, 0);
	for (i = -Dim; i < Dim; i++) {
		glVertex3f(i, Y, -Dim);
		glVertex3f(i, Y, Dim);
	}
	for (i = -Dim; i < Dim; i++) {
		glVertex3f(-Dim, Y, i);
		glVertex3f(Dim, Y, i);
	}
	glEnd();

}
void DisegnaSfera(Vector3 pos, float R)
{
	int i;
	float j, X1, Y1, X2, Y2, s, c;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glMaterialfv(GL_FRONT, GL_AMBIENT, verde2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rosso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bianco);
	glMateriali(GL_FRONT, GL_SHININESS, 20);

	X2 = 0;
	Y2 = -1;
	for (i = 1; i <= 64; i++) {
		Y1 = Y2;
		X1 = X2;
		Y2 = (i / 32.0f) - 1.0f;
		X2 = 1 - (Y2 * Y2);
		if (X2 > 0) X2 = R * sqrt(X2);
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j < 6.2831f; j += (6.283f / 64)) {
			s = sin(j);
			c = cos(j);
			glNormal3f(c * X1, Y1, s * X1);
			glVertex3f(c * X1 * R, Y1 * R, s * X1 * R);
			glNormal3f(c * X2, Y2, s * X2);
			glVertex3f(c * X2 * R, Y2 * R, s * X2 * R);
		}
		glEnd();
	}

	glPopMatrix();
}
static void VisualizzaSistema()
{
	DisegnaPianoXZ(-5);
	DisegnaSfera(rBSphere0->GetPosition(), 1);
	DisegnaSfera(rBSphere1->GetPosition(), 1);
}
static void TastoPremuto(unsigned char Tasto){}
HDC			hDC = NULL;
HGLRC		hRC = NULL;
HWND		hWnd = NULL;
HINSTANCE	hInstance;
bool	keys[256];
bool	active = TRUE;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	// matrice
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -12);						
}
static GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat aLite[] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat dLite[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static GLfloat sLite[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static GLfloat LucePos[4] = { 1, 2, 1, 0 };
static int InitGL()									
{
	// Z buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// luci
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	return TRUE;								
}
DWORD StartTempo = 0;
static int DrawGLScene()						
{
	double t;

	if (StartTempo == 0) {
		t = 0.001;
		StartTempo = timeGetTime();
	}
	else {
		t = (timeGetTime() - StartTempo) / 1000.0;
	}

	while (TempoTotale < t) {
		p.ComputePhysic();
		TempoTotale += DT;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_AMBIENT, aLite);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dLite);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sLite);
	glLightfv(GL_LIGHT0, GL_POSITION, LucePos);

	VisualizzaSistema();

	return TRUE;								
}
static GLvoid KillGLWindow()					
{
	if (hRC != NULL) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL, _T("Release Of DC And RC Failed."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, _T("Release Rendering Context Failed."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;								
	}

	if (hDC != NULL && !ReleaseDC(hWnd, hDC)) {
		MessageBox(NULL, _T("Release Device Context Failed."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		hDC = NULL;							
	}

	if (hWnd != NULL && !DestroyWindow(hWnd)) {
		MessageBox(NULL, _T("Could Not Release hWnd."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;						
	}

	if (!UnregisterClass(_T("Physic Lib"), hInstance)) {
		MessageBox(NULL, _T("Could Not Unregister Class."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;						
	}
}
static BOOL CreateGLWindow(const char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = _T("Physic Lib");								// Set The Class Name

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, _T("Failed To Register The Window Class."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		_T("Physic Lib"),							// Class Name
		_T("Physic Lib"),								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, _T("Window Creation Error."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd))) {
		KillGLWindow();				
		MessageBox(NULL, _T("Can't Create A GL Device Context."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;				
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
		KillGLWindow();				
		MessageBox(NULL, _T("Can't Find A Suitable PixelFormat."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;				
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
		KillGLWindow();				
		MessageBox(NULL, _T("Can't Set The PixelFormat."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;				
	}

	if (!(hRC = wglCreateContext(hDC))) {
		KillGLWindow();				
		MessageBox(NULL, _T("Can't Create A GL Rendering Context."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;				
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		KillGLWindow();				
		MessageBox(NULL, _T("Can't Activate The GL Rendering Context."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;				
	}

	ShowWindow(hWnd, SW_SHOW);		
	SetForegroundWindow(hWnd);		
	SetFocus(hWnd);					
	ReSizeGLScene(width, height);	

	if (!InitGL()) {
		KillGLWindow();				
		MessageBox(NULL, _T("Initialization Failed."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;		
	}

	return TRUE;
}
LRESULT CALLBACK WndProc(HWND	hWnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch (uMsg) {
	case WM_ACTIVATE:
		if (!HIWORD(wParam)) {
			active = TRUE;
		}
		else {
			active = FALSE;
		}
		return 0;
	case WM_SYSCOMMAND:
		switch (wParam) {
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;		
		}
		break;				
	case WM_CLOSE:			
		PostQuitMessage(0);	
		return 0;			
	case WM_KEYDOWN:		
		keys[wParam] = TRUE;
		TastoPremuto(wParam);
		return 0;			
	case WM_KEYUP:				
		keys[wParam] = FALSE;	
		return 0;				
	case WM_SIZE:				
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); 
		return 0;								
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	
	//Vector3 zeros(0.0f, 0.0f, 0.0f);
	//SphereCollider* sC = new SphereCollider(rB->GetPosition(), zeros, 5.0);
	SphereCollider* sC0 = new SphereCollider(rBSphere0->GetPosition(), 5.0);
	rBSphere0->AttachCollider(sC0);
	p.AddRigidBody(*rBSphere0, rBSphere0->GetID());
	rBSphere0->ApplyForce(Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 3.0f, 4.0f));

	SphereCollider* sC1 = new SphereCollider(rBSphere1->GetPosition(), 5.0);
	rBSphere1->AttachCollider(sC1);
	p.AddRigidBody(*rBSphere1, rBSphere1->GetID());
	rBSphere1->ApplyForce(Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 3.0f, 4.0f));




	MSG		msg;
	BOOL	done = FALSE;
	if (!CreateGLWindow("Physic Lib", 600, 600)) {
		return 0;
	}
	timeBeginPeriod(1);
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				done = TRUE;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			if (active) {
				if (keys[VK_ESCAPE]) {
					done = TRUE;
				}
				else {
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
		}
	}

	timeEndPeriod(1);
	KillGLWindow();
	return (msg.wParam);
}
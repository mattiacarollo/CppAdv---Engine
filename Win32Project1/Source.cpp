//--------------------------------------------------------------------------------------
// Copyright (c) Luca Giona 2013. Do not distribute. (Master Game Development - University of Verona)
//--------------------------------------------------------------------------------------

#include <Windows.h>
#include <d3d11.h>

// Variabili globali
HINSTANCE g_hInst = nullptr;
HWND g_hWnd = nullptr;
D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

// Prototipi funzioni
HRESULT initializeWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT initializeDevice();
void cleanupDevice();
void render();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // window callback

// Main per applicazioni windows.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(initializeWindow(hInstance, nCmdShow)))
		return 1;

	if (FAILED(initializeDevice()))
	{
		cleanupDevice();
		return 1;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			render();
		}
	}

	// Pulizia finale
	cleanupDevice();

	return (int)msg.wParam;
}

HRESULT initializeWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Descrizione della nostra finestra
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);

	// Registrazione della classe
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Creazione della finestra
	g_hInst = hInstance;
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); // Calcola bordi per avere un'effettiva vista a 800x600
	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Inizializzazione DX11 con API Windows", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	if (!g_hWnd)
		return E_FAIL;

	// Mostra la finestra
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

// Callback per la gestione dei messaggi di Windows.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
	{
		// Chiamato ogni volta si necessita di ridisegnare qualcosa a schermo
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	} break;

	case WM_DESTROY:
	{
		// Chiamato prima di uscire dall'applicazione
		PostQuitMessage(0);
	} break;

	default:
	{
		// Per tutti gli altri eventi, lascia a Windows gestire le chiamate
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return 0;
}

// Inizializzazione DX11
HRESULT initializeDevice()
{
	HRESULT hr = S_OK;

	// Registra l'area in cui compare la finestra
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	// Crea un device in modalità debug
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Lo swap chain è responsabile del rendering a schermo effettivo. 
	// Solitamente è inizializzato in modalità double buffered, ovvero contiene solitamente due buffer: front e back
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	// Numero di buffer
	sd.BufferCount = 1; // Numero di Back_buffer
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Formato RGBA a 32bit
	sd.BufferDesc.RefreshRate.Numerator = 60; // Refresh rate schermo
	sd.BufferDesc.RefreshRate.Denominator = 1; // Fattore di divisione refresh rate (intero)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Utilizzo del backbuffer: il rendering viene scritto qui
	sd.OutputWindow = g_hWnd; // handler finistra
	sd.SampleDesc.Count = 1; // Serve per il multisampling - in questo caso viene disabilitato
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE; // Modalità fullscree/windows

	// Definisce quali tipi di driver compatibili cercare
	// Hardware: utilizza schede video. Reference: se il driver "emula" in modo software alcune funzioni. (_Null : driver incapace di effettuare il rendering)
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		// Prova ad inizializzare per i tipi di driver definiti
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, g_driverType, nullptr, createDeviceFlags, nullptr, 0,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, nullptr, &g_pd3dDeviceContext);
		// Appena funziona esci
		if (SUCCEEDED(hr))
			break;
	}

	// Errore: niente di buono qui.
	if (FAILED(hr))
		return hr;

	// Ottieni il backbuffer. Il back buffer è semplicemente una texture 2d. Una texture 2d è semplicemente una matrice bidimensionale di valori.
	ID3D11Texture2D* pBackBuffer;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// Crea il render target e collega l'output alla texture 2d
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Collega il buffer al merger stage in modo che l'output sia effettuato qui
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

	// Setta il viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDeviceContext->RSSetViewports(1, &vp);

	return S_OK;
}

// Pulizia della memoria e distruzione degli oggetti creati
void cleanupDevice()
{
	// Controllate sempre che i puntatori non siano NULL con if
	// prima di rilasciare il device è ripristanare gli stati iniziali
	if (g_pd3dDevice)
		g_pd3dDeviceContext->ClearState();

	if (g_pRenderTargetView)
		g_pRenderTargetView->Release();

	if (g_pSwapChain)
		g_pSwapChain->Release();

	if (g_pd3dDevice)
		g_pd3dDevice->Release();
}

void render()
{
	// Pulisce il colore di sfondo (cornflower blue).
	float clearColor[4] = { 0.39f, 0.58f, 0.93f, 1.0f }; //rgba

	g_pd3dDeviceContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);

	// Effettua uno swap dei buffer
	g_pSwapChain->Present(0, 0);
}

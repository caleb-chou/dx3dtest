#include <Windows.h>

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE: 
		PostQuitMessage(69); 
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow) 
{
	const auto pClassName = "DX3D Project";

	// Registering window
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIcon = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = nullptr;
	RegisterClassEx( &wcex );

	// Creating Window Instace
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		"DX3D Project Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		200, 200, 1280, 720,
		nullptr, nullptr, hInstance, nullptr
	);

	// Show window instance
	ShowWindow(hWnd, SW_SHOW);

	// Message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult < 0)
		return -1;
	else
		return msg.wParam;
}
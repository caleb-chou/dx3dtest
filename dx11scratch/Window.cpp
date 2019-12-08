#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
	hInst(GetModuleHandle(nullptr)) {

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = handleMessageSetup;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = getInstance();
	wcex.hIcon = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = getName();
	wcex.hIconSm = nullptr;
	RegisterClassEx(&wcex);
}
Window::WindowClass::~WindowClass() {
	UnregisterClass(wndClassName, getInstance());
}

const char* Window::WindowClass::getName() noexcept {
	return wndClassName;
}

HINSTANCE Window::WindowClass::getInstance() noexcept {
	return wndClass.hInst;
}

Window::Window(int w, int h, const char* name) noexcept {
	RECT wr;
	wr.left = 100;
	wr.right = w + wr.left;
	wr.top = 100;
	wr.bottom = h + wr.top;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		WindowClass::getName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, 
		nullptr, nullptr, WindowClass::getInstance(),this
	);

	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	if (msg == WM_CREATE) {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate -> lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMessage));
		return pWnd->handleMsg( hWnd, msg, wParam,lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	switch (msg) {
		case WM_CLOSE: {
				PostQuitMessage(0);
				break;
			}
		case WM_KEYDOWN:
			switch (wParam) {
				{
			case 'W':
				SetWindowText(hWnd, "W");
				break;
			case 'A':
				SetWindowText(hWnd, "A");
				break;
			case 'S':
				SetWindowText(hWnd, "S");
				break;
			case 'D':
				SetWindowText(hWnd, "D");
				break;
				}
				break;
			}
		case WM_KEYUP: {
			break;
		}
		case WM_CHAR: {
			break;
		}
		case WM_LBUTTONDOWN: {
			break;
		}
		case WM_RBUTTONDOWN: {
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
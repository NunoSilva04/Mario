#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#include "D3D.h"	
#include "InputManager.h"

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LARGE_INTEGER start_time, end_time, frequency;
LARGE_INTEGER start_frame, end_frame;
float frame_time;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int CmdShow) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Window class
	HWND hWnd;

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if (RegisterClassEx(&windowClass) == NULL) {
		MessageBox(nullptr, L"Couldn't create window class", L"Error", MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(NULL, L"MainWindow", L"Mario", WS_POPUP, 0, 0, width, height,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, CmdShow);

	//Initialize D3D (everything)
	D3D d3d;
	d3d.initD3D(hWnd);

	//Time
	int time = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start_time);
	QueryPerformanceCounter(&start_frame);

	//Message Loop
	MSG msg = { 0 };
	while (true) {
		ShowCursor(false);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			//Get time
			QueryPerformanceCounter(&end_time);
			time = (end_time.QuadPart - start_time.QuadPart) / (float)frequency.QuadPart;
			//Get frame time
			QueryPerformanceCounter(&end_frame);
			frame_time = (end_frame.QuadPart - start_frame.QuadPart) / (float)frequency.QuadPart;

			//Run D3D
			d3d.updateD3D(frame_time);
			d3d.renderD3D(time);

			start_frame = end_frame;
		}
	}

	d3d.cleanD3D();
	return msg.wParam;
}



LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			DestroyWindow(hWnd);
		}
		inputManager.keyPressed[wParam] = true;
		break;
	
	case WM_KEYUP:
		inputManager.keyPressed[wParam] = false;
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
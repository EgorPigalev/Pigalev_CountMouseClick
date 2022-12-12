#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam);
DWORD LKey = 0; RKey = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HHOOK hHook = SetWindowsHookExW(WH_MOUSE_LL, LogMouse, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	MessageBox(NULL, LKey, L"Количество нажатий левой кнопкой мыши", MB_OK);
	return 0;
}

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == 513)
	{
		LKey++;
	}
	if (wParam == 516)
	{
		RKey++;
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(char* wstr);
int LKey = 0;
int RKey = 0;
int KKey;
int KTKey;
int KBKey;

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
	if (wParam == 519)
	{
		KKey++;
	}
	if (wParam == 522)
	{
		MSLLHOOKSTRUCT* mouseInfo = (MSLLHOOKSTRUCT*)lParam;
		if (mouseInfo->mouseData == 4287102976)
		{
			KBKey++;
		}
		if (mouseInfo->mouseData == 7864320)
		{
			KTKey++;
		}
	}
	char* str = calloc(500, sizeof(char));
	sprintf(str, "Количество нажатий ЛКМ: %d\nКоличество нажатий ПКМ: %d\nКоличество нажатий на колесико: %d\nКоличество прокруток колёсиком вверх: %d\nКоличество прокруток колёсиком вниз: %d", LKey, RKey, KKey, KTKey, KBKey);
	WriteToFile(str);
	free(str);
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WriteToFile(char* wstr)
{
	HANDLE fileResult = CreateFile(L"..\\ContMouse.txt",    // создаваемый файл
		GENERIC_WRITE,         // открывается для записи
		FILE_SHARE_WRITE,      // совместно не используется
		NULL,                  // защита по умолчанию
		CREATE_ALWAYS,         // переписывает существующий
		FILE_ATTRIBUTE_HIDDEN,  // асинхронный ввод/вывод I/O
		NULL);                 // атрибутов шаблона нет
	DWORD d;
	WriteFile(fileResult, wstr, strlen(wstr), &d, NULL);
	CloseHandle(fileResult);
}
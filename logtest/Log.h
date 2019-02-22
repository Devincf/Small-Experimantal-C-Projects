#pragma once
#ifndef LOG_H
#define LOG_H

#include <string>
#include <Windows.h>
#include <iostream>

using namespace std;

const enum COLOR {
	BLACK = 0,
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	DARK_CYAN = 3,
	DARK_RED = 4,
	DARK_PURPLE = 5,
	DARK_YELLOW = 6,
	DARK_WHITE = 7,
	GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_PURPLE = 13,
	LIGHT_YELLOW = 14,
	LIGHT_WHITE = 15,
};

static bool initialized = false;
class Log {
public:

	~Log() {
	}

	Log() {
		if (!initialized) {
			InitializeConsole();
			initialized = true;
		}
	}
	void ClearConsole() {
		for (int i = 0; i < 50; i++) {
			cout << "" << endl;
		}
		cout << "\x1B[H";
	}

	void WriteLog(string t) {
		setColor(COLOR::BLACK, COLOR::DARK_WHITE);
		cout << "[LOG] ";
		resetColor();
		cout << t.c_str() << "\n";
		//WriteLogToFile(t);
	}
	void WriteSuccessLog(string t) {
		setColor(COLOR::DARK_GREEN, COLOR::DARK_WHITE);
		cout << "[SUCCESS] ";
		resetColor();
		cout << t.c_str() << "\n";
		//WriteSuccessLogToFile(t);
	}
	void WriteErrorLog(string t) {
		setColor(COLOR::LIGHT_RED, COLOR::DARK_WHITE);
		cout << "[ERROR] ";
		resetColor();
		cout << t.c_str() << "\n";
		//WriteErrorLogToFile(t);
	}
	void WriteWarningLog(string t) {
		setColor(COLOR::LIGHT_YELLOW, COLOR::DARK_WHITE);
		cout << "[!] ";
		resetColor();
		cout << t.c_str() << "\n";
		//WriteWarningLogToFile(t);
	}
private:
	HANDLE hConsoleInput, hConsoleOutput;
	FILE *fstreamin, *fstreamout;
	HWND ConsoleWindow;
	RECT cRect;


	const WORD calculateColor(const COLOR c1, const COLOR c2) const { return c1 + c2 * 16; }
	const void resetColor() {
		setColor(COLOR::BLACK, COLOR::DARK_WHITE);
	}

	const void setColor(const COLOR c1, const COLOR c2) {
		if (SetConsoleTextAttribute(hConsoleOutput, calculateColor(c1, c2)) == NULL) {
			return;
		}
	}

	const void loadConsoleRect() {
		GetWindowRect(ConsoleWindow, &cRect);
	}

	const void loadConsoleIO() {
		if (AllocConsole() == NULL) {
			return;
		}

		freopen_s(&fstreamin, "CONIN$", "r", stdin);
		freopen_s(&fstreamout, "CONOUT$", "w", stdout);
		freopen_s(&fstreamout, "CONOUT$", "w", stderr);

		hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		ConsoleWindow = GetConsoleWindow();

	}
	const void loadConsoleFont() {
		CONSOLE_FONT_INFOEX cInfo;
		COORD cFontSize;
		cFontSize.X = 13;
		cFontSize.Y = 20;
		cInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(hConsoleOutput, false, &cInfo);
		cInfo.dwFontSize = cFontSize;
		SetCurrentConsoleFontEx(hConsoleOutput, false, &cInfo);
	}
	const void loadConsoleBuffer() {
		CONSOLE_SCREEN_BUFFER_INFO SBInfo;
		COORD NewSBSize;
		int Status;
		GetConsoleScreenBufferInfo(hConsoleOutput, &SBInfo);
		NewSBSize.X = SBInfo.dwSize.X;
		NewSBSize.Y = 30;
		Status = SetConsoleScreenBufferSize(hConsoleOutput, NewSBSize);
	}
	const void InitializeConsole() {
		loadConsoleIO();
		loadConsoleRect();
		loadConsoleFont();
		loadConsoleBuffer();


		MoveWindow(ConsoleWindow, cRect.left, cRect.top, 1200, 700, TRUE);
		system("color 70");


		WriteLog("Testing All Logging Functionality...");
		Sleep(100);
		WriteLog("Default Log Test");
		Sleep(30);
		WriteSuccessLog("Success Log Test");
		Sleep(30);
		WriteErrorLog("Error Log Test");
		Sleep(30);
		WriteWarningLog("Warning Log Test");
		Sleep(600);


		WriteSuccessLog("successfully loaded console");
		Sleep(200);

		ClearConsole();

	}
};
static Log LOGGER = Log();
#endif
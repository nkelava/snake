#include "Console.h"

#ifdef _WIN32

#include <conio.h>
#include <cstdlib>
#include <windows.h>

int Console::getKey() {
	return _getch();
}

bool Console::keyPressed() {
	return _kbhit();
}

void Console::sleepFor(int milliseconds) {
	Sleep(milliseconds);
}

void Console::clearScreen() {
	system("cls");
}

void Console::flushInput() {
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}

#else

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

namespace {
	termios originalSettings;
	bool rawMode = false, screenCleared = false;
	int pendingKey = -1; // Second code of an arrow key

	void restoreTerminal() {
		if (rawMode) {
			tcsetattr(STDIN_FILENO, TCSANOW, &originalSettings);
			rawMode = false;
		}
		const char clearBelow[] = "\x1b[J"; // Clear what is left below the last screen
		ssize_t written = write(STDOUT_FILENO, clearBelow, sizeof(clearBelow) - 1);
		(void)written;
	}

	void handleSignal(int signalNumber) {
		restoreTerminal();
		signal(signalNumber, SIG_DFL);
		raise(signalNumber);
	}

	void enableRawMode() {
		if (rawMode || !isatty(STDIN_FILENO)) { return; }

		tcgetattr(STDIN_FILENO, &originalSettings);
		termios raw = originalSettings;
		raw.c_lflag &= ~(ICANON | ECHO); // Read keys one by one, without printing them
		raw.c_cc[VMIN] = 1;
		raw.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
		rawMode = true;

		atexit(restoreTerminal);
		signal(SIGINT, handleSignal);
		signal(SIGTERM, handleSignal);
	}

	bool inputAvailable(int timeoutMs) {
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		timeval timeout = { 0, timeoutMs * 1000 };
		return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &timeout) > 0;
	}

	int readByte() {
		unsigned char c;
		return (read(STDIN_FILENO, &c, 1) == 1) ? c : -1;
	}
}

int Console::getKey() {
	enableRawMode();
	std::cout << std::flush;

	if (pendingKey != -1) {
		int key = pendingKey;
		pendingKey = -1;
		return key;
	}

	int c = readByte();

	if (c == -1) { return 27; } // No more input, act like Esc so the game can exit
	if (c == '\n') { return 13; } // Enter
	if (c == 127) { return 8; } // Backspace

	if (c == 27) {
		// Arrow keys are sent as Esc [ A-D, a single Esc is the Esc key
		if (!inputAvailable(50)) { return 27; }

		int c2 = readByte();
		if ((c2 == '[' || c2 == 'O') && inputAvailable(50)) {
			switch (readByte()) {
			case 'A': pendingKey = 72; return 224; // Up
			case 'B': pendingKey = 80; return 224; // Down
			case 'C': pendingKey = 77; return 224; // Right
			case 'D': pendingKey = 75; return 224; // Left
			}
		}
		// Ignore other escape sequences (function keys, Delete, ...)
		while (inputAvailable(0)) { readByte(); }
		return getKey();
	}
	return c;
}

bool Console::keyPressed() {
	enableRawMode();
	return pendingKey != -1 || inputAvailable(0);
}

void Console::sleepFor(int milliseconds) {
	std::cout << std::flush;
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Console::clearScreen() {
	enableRawMode();
	// Erase the screen only the first time, after that draw over it to avoid flickering
	std::cout << (screenCleared ? "\x1b[H" : "\x1b[2J\x1b[H") << std::flush;
	screenCleared = true;
}

void Console::flushInput() {
	enableRawMode();
	pendingKey = -1;
	tcflush(STDIN_FILENO, TCIFLUSH);
}

#endif

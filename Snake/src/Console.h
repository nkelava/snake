#pragma once

// Platform-specific console input and output (Windows, Linux, macOS)
namespace Console {
	// Waits for a key press. Arrow keys return 224 followed by the key code on the next call, same as _getch() on Windows
	int getKey();
	bool keyPressed();
	void sleepFor(int milliseconds);
	void clearScreen();
	void flushInput();
}

#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#include "consoleInteraction.hpp"

void repeatChar(char c, int num, bool newline = false) {
	for (int i = 0; i < num; i++) { std::cout << c; }
	if (newline) { std::cout << "\n"; }
}

void rectangle(
	int x, int y, 
	int width, int height, bool reset = false, 
	int borderWidth = 1, char borderChar = '#', 
	bool fill = false, char fillChar = ' '
) {
	move(x, y);

	for (int i = 0; i < borderWidth; i++) {
		repeatChar(borderChar, width, true);
	}

	for (int i = 0; i < height - (borderWidth * 2); i++) {
		repeatChar(borderChar, borderWidth);
		repeatChar(fillChar, (width - borderWidth * 2));
		repeatChar(borderChar, borderWidth, true);
	}

	for (int i = 0; i < borderWidth; i++) {
		repeatChar(borderChar, width);
	}

	if(reset) {
		move(cursorRetX, cursorRetY);
	}
	else {
		cursorRetX = x;
		cursorRetY = y;
	}
}

void line(int x1, int y1, int x2, int y2, bool reset = false) {
	//Implement closest line algorithm
}

#endif
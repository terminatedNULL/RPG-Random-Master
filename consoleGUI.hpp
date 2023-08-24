#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#include <math.h>

#include "globals.hpp"
#include "definitions.hpp"
#include "consoleInteraction.hpp"

void repeatChar(char c, int num, bool newline = false) {
	for (int i = 0; i < num; i++) { std::cout << c; }
	if (newline) { std::cout << "\n"; }
}

cGUI::Rectangle rectangle(
	int x, int y, 
	int width, int height, bool reset = false, 
	int borderWidth = 1, char borderChar = '#', 
	bool fill = false, char fillChar = ' '
) {
	cGUI::Rectangle rect = {
		x, y,
		width, height,
		borderChar,
		borderWidth,
		fillChar,
		currTextCol,
		currBackCol
	};

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

	return rect;
}

void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset = 0, int yOffset = 0
) {
	rect.text[position] = text;
	switch (position) {
	case cGUI::TOP_LEFT:
		move(
			rect.x + rect.borderWidth + 1 + xOffset,
			rect.y + rect.borderWidth + 1 + yOffset
		);
		break;
	case cGUI::TOP_CENTER:
		move(
			rect.x + rect.borderWidth + 1 + 
				(rect.width - text.length()) / 2 + xOffset,
			rect.y + rect.borderWidth + 1 + yOffset
		);
		break;
	case cGUI::TOP_RIGHT:
		move(
			rect.x + rect.width - text.length() + xOffset,
			rect.y + rect.borderWidth + 1 + yOffset
		);
		break;
	case cGUI::LEFT_CENTER:
		move(
			rect.x + rect.borderWidth + 1 + xOffset,
			rect.y + 1 + rect.height / 2 + yOffset
		);
		break;
	case cGUI::CENTER:
		move(
			rect.x + rect.borderWidth + 1 +
				(rect.width - text.length()) / 2 + xOffset,
			rect.y + 1 + 
				rect.height / 2 + yOffset
		);
		break;
	case cGUI::RIGHT_CENTER:
		move(
			rect.x + rect.width - text.length()
				+ xOffset,
			rect.y + 1 + rect.height / 2 + yOffset
		);
		break;
	case cGUI::BOTTOM_LEFT:
		move(
			rect.x + rect.borderWidth + 1 + xOffset,
			rect.y + rect.height - rect.borderWidth + yOffset
		);
		break;
	case cGUI::BOTTOM_CENTER:
		move(
			rect.x + rect.borderWidth + 1 +
			(rect.width - text.length()) / 2 + xOffset,
			rect.y - rect.borderWidth + rect.height + yOffset
		);
		break;
	case cGUI::BOTTOM_RIGHT:
		move(
			rect.x + rect.width - text.length() + xOffset,
			rect.y - rect.borderWidth + rect.height + yOffset
		);
		break;
	}
	std::cout << text;
}

void line(int x1, int y1, int x2, int y2, bool reset = false) {
	//Implement closest line algorithm
}

#endif
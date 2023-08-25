#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#include <math.h>

#include "globals.hpp"
#include "definitions.hpp"
#include "consoleInteraction.hpp"

//////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////

void repeatChar(char c, int num, bool newline = false);
cGUI::Rectangle createRectangle(
	int x, int y,
	int width, int height,
	int borderWidth = 1, char borderChar = '#',
	bool fill = false, char fillChar = ' '
);
cGUI::FancyRectangle createFancyRectangle(
	int x, int y,
	int width, int height,
	int borderWidth = 1,
	std::string cornerChars = "■■■■",
	char horizontalChar = '|', char verticalChar = '-',
	char fillChar = ' '
);
void drawRectangle(cGUI::Rectangle& rect);
void drawRectangle(cGUI::FancyRectangle& rect);
void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset = 0, int yOffset = 0
);
void setRectColor(
	cGUI::Rectangle& rect,
	cGUI::RGB borderCol, cGUI::RGB fillCol, cGUI::RGB textCol
);
void setRectColor(
	cGUI::FancyRectangle& rect,
	cGUI::RGB cornerCol, cGUI::RGB horizCol, cGUI::RGB vertCol,
	cGUI::RGB fillCol, cGUI::RGB textCol
);
void line(int x1, int y1, int x2, int y2, bool reset = false);

//////////////////////////////////////////////////////////////////////////////
// FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////////////////////

void repeatChar(char c, int num, bool newline) {
	for (int i = 0; i < num; i++) { std::cout << c; }
	if (newline) { std::cout << "\n"; }
}

cGUI::Rectangle createRectangle(
	int x, int y, 
	int width, int height, 
	int borderWidth, char borderChar, 
	bool fill, char fillChar
) {
	cGUI::Rectangle rect = {
		x, y,
		width, height,
		borderWidth,
		borderChar,
		fillChar,
		currTextCol,
		currBackCol,
		{ 255, 255, 255 }
	};

	drawRectangle(rect);

	move(x, y);

	return rect;
}

cGUI::FancyRectangle createFancyRectangle(
	int x, int y,
	int width, int height,
	int borderWidth,
	std::string cornerChars,
	char horizontalChar, char verticalChar,
	char fillChar
) {
	cGUI::FancyRectangle rect = {

	};

	return rect;
}

void drawRectangle(cGUI::Rectangle& rect) {
	setTextColor(rect.borderColor);
	for (int i = 0; i < rect.borderWidth; i++) {
		repeatChar(rect.borderChar, rect.width, true);
	}

	for (int i = 0; i < rect.height - (rect.borderWidth * 2); i++) {
		repeatChar(rect.borderChar, rect.borderWidth);
		setTextColor(rect.fillColor);
		repeatChar(rect.fillChar, (rect.width - rect.borderWidth * 2));
		setTextColor(rect.borderColor);
		repeatChar(rect.borderChar, rect.borderWidth, true);
	}

	for (int i = 0; i < rect.borderWidth; i++) {
		repeatChar(rect.borderChar, rect.width);
	}

	setTextColor(rect.textColor);
	setRectText(rect, rect.text, rect.textPos);
}

void drawRectangle(cGUI::FancyRectangle& rect) {

}

void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset, int yOffset
) {
	rect.text = text;
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

void setRectColor(
	cGUI::Rectangle &rect, 
	cGUI::RGB borderCol, cGUI::RGB fillCol, cGUI::RGB textCol
) {
	if (borderCol.r != -1) { rect.borderColor = borderCol; }
	if (fillCol.r != -1) { rect.fillColor = fillCol; }
	if (textCol.r != -1) { rect.textColor = textCol; }
	drawRectangle(rect);
}

void setRectColor(
	cGUI::FancyRectangle& rect,
	cGUI::RGB cornerCol, cGUI::RGB horizCol, cGUI::RGB vertCol,
	cGUI::RGB fillCol, cGUI::RGB textCol
) {
	if (cornerCol.r != -1) { rect.cornerColor = cornerCol; }
	if (horizCol.r != -1) { rect.horizontalColor = horizCol; }
	if (vertCol.r != -1) { rect.verticalColor = vertCol; }
	if (fillCol.r != -1) { rect.fillColor = fillCol; }
	if (textCol.r != -1) { rect.textColor = textCol; }
	drawRectangle(rect);
}

void line(int x1, int y1, int x2, int y2, bool reset) {
	//Implement closest line algorithm
}

#endif
#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#include <math.h>

#include "globals.hpp"
#include "definitions.hpp"
#include "consoleInteraction.hpp"

//////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////

cGUI::Rectangle createRectangle(
	int x, int y,
	int width, int height,
	int borderWidth = 1, char borderChar = '#',
	bool fill = false, char fillChar = ' '
);
int cornerDefault[4] = { 254, 254, 254, 254 };
cGUI::FancyRectangle createFancyRectangle(
	int x, int y,
	int width, int height,
	int borderWidth = 1,
	int cornerChars[4] = cornerDefault,
	char horizontalChar = '-', char verticalChar = '|',
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
		{ 255, 255, 255 },
		"", cGUI::NO_HANDLE,
		-1, -1
	};

	drawRectangle(rect);
	return rect;
}

cGUI::FancyRectangle createFancyRectangle(
	int x, int y,
	int width, int height,
	int borderWidth,
	int cornerChars[4],
	char horizontalChar, char verticalChar,
	char fillChar
) {
	cGUI::FancyRectangle rect = {
		x, y, 
		width, height, 
		borderWidth, cornerChars,
		horizontalChar, verticalChar, fillChar,
		{ 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 },
		{ 0, 0, 0 }, { 255, 255, 255 },
		"", cGUI::NO_HANDLE,
		-1, -1
	};

	drawRectangle(rect);

	return rect;
}

void drawRectangle(cGUI::Rectangle& rect) {
	clearColors();
	move(rect.x, rect.y);

	setTextColor(rect.borderColor);
	for (int i = 0; i < rect.borderWidth; i++) {
		repeatChar(rect.borderChar, rect.width, true);
	}

	for (int i = 0; i < rect.height - (rect.borderWidth * 2); i++) {
		repeatChar(rect.borderChar, rect.borderWidth, false);
		setBackgroundColor(rect.fillColor);
		repeatChar(rect.fillChar, (rect.width - rect.borderWidth * 2), false);
		clearColors();
		setTextColor(rect.borderColor);
		repeatChar(rect.borderChar, rect.borderWidth, true);
	}

	for (int i = 0; i < rect.borderWidth; i++) {
		repeatChar(rect.borderChar, rect.width, false);
	}

	if (rect.textX != -1) {
		move(rect.textX, rect.textY);
		setTextColor(rect.textColor);
		setBackgroundColor(rect.fillColor);
		std::cout << rect.text;
		clearColors();
	}
}

void drawRectangle(cGUI::FancyRectangle& rect) {
	clearColors();
	move(rect.x, rect.y);

	setTextColor(rect.cornerColor);
	repeatExtChar(rect.cornerChars[0], rect.borderWidth, false);
	setTextColor(rect.horizontalColor);
	repeatExtChar(rect.horizontalChar, rect.width - (rect.borderWidth * 2), false);
	setTextColor(rect.cornerColor);
	repeatExtChar(rect.cornerChars[1], rect.borderWidth, false);

	for (int i = 0; i < rect.height - (rect.borderWidth * 2); i++) {
		setTextColor(rect.verticalColor);
		repeatExtChar(rect.verticalChar, rect.borderWidth, false);
		setTextColor(rect.fillColor);
		repeatExtChar(rect.fillChar, rect.width - (rect.borderWidth * 2), false);
		setTextColor(rect.verticalColor);
		repeatExtChar(rect.verticalChar, rect.borderWidth, false);
	}

	setTextColor(rect.cornerColor);
	repeatExtChar(rect.cornerChars[0], rect.borderWidth, false);
	setTextColor(rect.horizontalColor);
	repeatExtChar(rect.horizontalChar, rect.width - (rect.borderWidth * 2), false);
	setTextColor(rect.cornerColor);
	repeatExtChar(rect.cornerChars[1], rect.borderWidth, false);
}

void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset, int yOffset
) {
	if (rect.x != -1 && rect.textPos == position) {
		move(rect.textX, rect.textY);
		std::cout << text;
		return;
	}

	rect.text = text;
	int tX = 0, tY = 0;

	switch (position) {
	case cGUI::TOP_LEFT:
		tX = rect.x + rect.borderWidth + 1 + xOffset;
		tY = rect.y + rect.borderWidth + 1 + yOffset;
		break;
	case cGUI::TOP_CENTER:
		tX = rect.x + rect.borderWidth + 1 + 
			 (rect.width - text.length()) / 2 + xOffset;
		tY = rect.y + rect.borderWidth + 1 + yOffset;
		break;
	case cGUI::TOP_RIGHT:
		tX = rect.x + rect.width - text.length() + xOffset;
		tY = rect.y + rect.borderWidth + 1 + yOffset;
		break;
	case cGUI::LEFT_CENTER:
		tX = rect.x + rect.borderWidth + 1 + xOffset;
		tY = rect.y + 1 + rect.height / 2 + yOffset;
		break;
	case cGUI::CENTER:
		tX = rect.x + rect.borderWidth + 1 +
			 (rect.width - text.length()) / 2 + xOffset;
		tY = rect.y + 1 + rect.height / 2 + yOffset;
		break;
	case cGUI::RIGHT_CENTER:
		tX = rect.x + rect.width - text.length() + xOffset;
		tY = rect.y + 1 + rect.height / 2 + yOffset;
		break;
	case cGUI::BOTTOM_LEFT:
		tX = rect.x + rect.borderWidth + 1 + xOffset;
		tY = rect.y + rect.height - rect.borderWidth + yOffset;
		break;
	case cGUI::BOTTOM_CENTER:
		tX = rect.x + rect.borderWidth + 1 +
			 (rect.width - text.length()) / 2 + xOffset;
		tY = rect.y - rect.borderWidth + rect.height + yOffset;
		break;
	case cGUI::BOTTOM_RIGHT:
		tX = rect.x + rect.width - text.length() + xOffset;
		tY = rect.y - rect.borderWidth + rect.height + yOffset;
		break;
	}
	rect.textX = tX;
	rect.textY = tY;

	move(tX, tY);
	setTextColor(rect.textColor);
	setBackgroundColor(rect.fillColor);
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
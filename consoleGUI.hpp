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
	bool fill = false, char fillChar = ' ', int state = cGUI::IDLE
);
int cornerDefault[4] = { 254, 254, 254, 254 };
cGUI::FancyRectangle createFancyRectangle(
	int x, int y,
	int width, int height,
	int borderWidth = 1,
	int cornerChars[4] = cornerDefault,
	char horizontalChar = '-', char verticalChar = '|',
	char fillChar = 32, int state = cGUI::IDLE
);
void drawRectangle(cGUI::Rectangle& rect);
void drawRectangle(cGUI::FancyRectangle& rect);
void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset = 0, int yOffset = 0
);
void setRectText(
	cGUI::FancyRectangle& rect, std::string text, cGUI::Handle position,
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
void setRectState(cGUI::Rectangle& rect, int state);
void setRectState(cGUI::FancyRectangle& rect, int state);
void setInteractionColors(
	cGUI::FancyRectangle& rect,
	cGUI::RGB idle, cGUI::RGB hover, cGUI::RGB click
);
void setRadio(cGUI::Rectangle& rect, bool state);
void setRadio(cGUI::FancyRectangle& rect, bool state);
void setOuterColors(cGUI::FancyRectangle& rect, cGUI::RGB color);
void setRectSide(cGUI::Rectangle& rect, cGUI::Handle side, bool state);
void line(int x1, int y1, int x2, int y2, bool reset = false);

//////////////////////////////////////////////////////////////////////////////
// FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////////////////////

cGUI::Rectangle createRectangle(
	int x, int y, 
	int width, int height, 
	int borderWidth, char borderChar, 
	bool fill, char fillChar, int state
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
		BLANK_RGB, BLANK_RGB, BLANK_RGB, 
		"", cGUI::NO_HANDLE,
		-1, -1, state
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
	char fillChar, int state
) {
	cGUI::FancyRectangle rect = {
		x, y, 
		width, height, 
		borderWidth, cornerChars,
		horizontalChar, verticalChar, fillChar,
		{ 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 },
		{ 0, 0, 0 }, { 255, 255, 255 },
		BLANK_RGB, BLANK_RGB, BLANK_RGB,
		"", cGUI::NO_HANDLE, -1, -1, state
	};

	drawRectangle(rect);

	return rect;
}

void drawRectangle(cGUI::Rectangle& rect) {
	if (rect.state == cGUI::DISABLED) { return; }
	clearColors();
	move(rect.x, rect.y);

	cGUI::RGB& borderColor = rect.borderColor;
	cGUI::RGB& fillColor = rect.fillColor;
	cGUI::RGB& textColor = rect.textColor;

	switch (rect.colorType) {
	case cGUI::INNER_COLOR:
		switch (rect.state) {
		case cGUI::IDLE:
			fillColor = rect.idleColor;
			break;
		case cGUI::HOVER:
			fillColor = rect.hoverColor;
			break;
		case cGUI::CLICK:
			fillColor = rect.clickColor;
			break;
		}
		break;
	case cGUI::OUTER_COLOR:
		switch(rect.state) {
	case cGUI::IDLE:
		borderColor = rect.idleColor;
		break;
	case cGUI::HOVER:
		borderColor = rect.hoverColor;
		break;
	case cGUI::CLICK:
		borderColor = rect.clickColor;
		break;
		}
		break;
	case cGUI::MOD_COLOR:
		borderColor + rect.colorMod;
		fillColor + rect.colorMod;
		textColor + rect.colorMod;
		break;
	}

	setTextColor(rect.borderColor);
	for (int i = 0; i < rect.borderWidth; i++) {
		repeatChar(rect.borderChar, rect.width, true);
	}

	for (int i = 0; i < rect.height - (rect.borderWidth * 2); i++) {
		repeatChar(rect.borderChar, rect.borderWidth, false);
		if (rect.fillChar == ' ') { setBackgroundColor(rect.fillColor); }
			else { setTextColor(rect.fillColor); }
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
	}
	clearColors();
}

void drawRectangle(cGUI::FancyRectangle& rect) {
	if (rect.state == cGUI::DISABLED) { return; }
	clearColors();
	move(rect.x, rect.y);

	cGUI::RGB &cornerColor = rect.cornerColor;
	cGUI::RGB &horizontalColor = rect.horizontalColor;
	cGUI::RGB &verticalColor = rect.verticalColor;
	cGUI::RGB &fillColor = rect.fillColor;
	cGUI::RGB &textColor = rect.textColor;

	switch (rect.colorType) {
	case cGUI::INNER_COLOR:
		switch (rect.state) {
		case cGUI::IDLE:
			fillColor = rect.idleColor;
			break;
		case cGUI::HOVER:
			fillColor = rect.hoverColor;
			break;
		case cGUI::CLICK:
			fillColor = rect.clickColor;
			break;
		}
		break;
	case cGUI::OUTER_COLOR:
		switch (rect.state) {
		case cGUI::IDLE:
			setOuterColors(rect, rect.idleColor);
			break;
		case cGUI::HOVER:
			setOuterColors(rect, rect.hoverColor);
			break;
		case cGUI::CLICK:
			setOuterColors(rect, rect.clickColor);
			break;
		}
		break;
	case cGUI::MOD_COLOR:
		cornerColor + rect.colorMod;
		horizontalColor + rect.colorMod;
		verticalColor + rect.colorMod;
		fillColor + rect.colorMod;
		textColor + rect.colorMod;
		break;
	}

	for (int i = 0; i < rect.borderWidth; i++) {
		if (!rect.sides[cGUI::TOP]) {
			repeatExtChar(' ', rect.width, false);
			break;
		}
		if (rect.sides[cGUI::LEFT]) {
			setTextColor(cornerColor);
			repeatExtChar(rect.cornerChars[0], rect.borderWidth, false);
		} else { repeatExtChar(' ', rect.borderWidth, false); }
		setTextColor(horizontalColor);
		repeatExtChar(rect.horizontalChar, rect.width - (rect.borderWidth * 2), false);
		if (rect.sides[cGUI::RIGHT]) {
			setTextColor(cornerColor);
			repeatExtChar(rect.cornerChars[1], rect.borderWidth, false);
		} else { repeatExtChar(' ', rect.borderWidth, false); }
		std::cout << "\n";
	}

	for (int i = 0; i < rect.height - (rect.borderWidth * 2); i++) {
		move(rect.x, rect.y + i + 1);
		if (rect.sides[cGUI::LEFT]) {
			setTextColor(verticalColor);
			repeatExtChar(rect.verticalChar, rect.borderWidth, false);
		} else { repeatExtChar(' ', rect.borderWidth, false); }
		if (rect.fillChar == ' ') { setBackgroundColor(fillColor); }
		else { setTextColor(fillColor); }
		repeatExtChar(rect.fillChar, rect.width - (rect.borderWidth * 2), false);
		clearColors();
		if (rect.sides[cGUI::RIGHT]) {
			setTextColor(verticalColor);
			repeatExtChar(rect.verticalChar, rect.borderWidth, false);
		} else { repeatExtChar(' ', rect.borderWidth, false); }
	}

	for (int i = 0; i < rect.borderWidth; i++) {
		if (!rect.sides[cGUI::BOTTOM]) { 
			repeatExtChar(' ', rect.width, false);
			break; 
		}
		move(rect.x, rect.y + rect.height - 1);
		if (rect.sides[cGUI::LEFT]) {
			setTextColor(cornerColor);
			repeatExtChar(rect.cornerChars[2], rect.borderWidth, false);
		} else { repeatExtChar(' ', rect.borderWidth, false); }
		setTextColor(horizontalColor);
		repeatExtChar(rect.horizontalChar, rect.width - (rect.borderWidth * 2), false);
		if (rect.sides[cGUI::RIGHT]) {
			setTextColor(cornerColor);
			repeatExtChar(rect.cornerChars[3], rect.borderWidth, false); \
		} else { repeatExtChar(' ', rect.borderWidth, false); }
	}

	if (rect.textX != -1) {
		move(rect.textX, rect.textY);
		setTextColor(textColor);
		setBackgroundColor(fillColor);
		std::cout << rect.text;
	}
}

void setRectText(
	cGUI::Rectangle& rect, std::string text, cGUI::Handle position,
	int xOffset, int yOffset
) {
	if (rect.state == cGUI::DISABLED) { return; }
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
		tY = rect.y + rect.height / 2 + yOffset;
		break;
	case cGUI::CENTER:
		tX = rect.x + rect.borderWidth + 1 +
			 (rect.width - text.length()) / 2 + xOffset;
		tY = rect.y + rect.height / 2 + yOffset;
		break;
	case cGUI::RIGHT_CENTER:
		tX = rect.x + rect.width - text.length() + xOffset;
		tY = rect.y + rect.height / 2 + yOffset;
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

void setRectText(
	cGUI::FancyRectangle& rect, std::string text, cGUI::Handle position,
	int xOffset, int yOffset
) {
	rect.text = text;
	if (rect.state == cGUI::DISABLED) { return; }
	if (rect.x != -1 && rect.textPos == position) {
		move(rect.textX, rect.textY);
		std::cout << text;
		return;
	}

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
		tY = rect.y + rect.height / 2 + yOffset;
		break;
	case cGUI::CENTER:
		tX = rect.x + rect.borderWidth + 1 +
			(rect.width - text.length()) / 2 + xOffset;
		tY = rect.y + rect.height / 2 + yOffset;
		break;
	case cGUI::RIGHT_CENTER:
		tX = rect.x + rect.width - text.length() + xOffset;
		tY = rect.y + rect.height / 2 + yOffset;
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

void setRectState(cGUI::Rectangle& rect, int state) {
	if (rect.state == state) { return; }

	rect.state = state;
	//Set rect colors based on state
	switch (rect.state) {
	case cGUI::DISABLED:
		rect.colorMod = -50;
		break;
	case cGUI::IDLE:
		rect.colorMod = 0;
		break;
	case cGUI::HOVER:
		rect.colorMod = 50;
		break;
	case cGUI::CLICK:
		rect.colorMod = 100;
		break;
	}

	drawRectangle(rect);
}

void setRectState(cGUI::FancyRectangle& rect, int state) {
	if (rect.state == state) { return; }

	rect.state = state;
	//Set rect colors based on state
	switch (rect.state) {
	case cGUI::DISABLED:
		rect.colorMod = -50;
		break;
	case cGUI::IDLE:
		rect.colorMod = 0;
		break;
	case cGUI::HOVER:
		rect.colorMod = 50;
		break;
	case cGUI::CLICK:
		rect.colorMod = 100;
		break;
	}

	drawRectangle(rect);
}

void setInteractionColors(
	cGUI::FancyRectangle& rect,
	cGUI::RGB idle, cGUI::RGB hover, cGUI::RGB click
) {
	rect.idleColor = idle;
	rect.hoverColor = hover;
	rect.clickColor = click;
}

void setRadio(cGUI::Rectangle &rect, bool state) {
	rect.radio = state;
	drawRectangle(rect);
}

void setRadio(cGUI::FancyRectangle &rect, bool state) {
	rect.radio = state;
	drawRectangle(rect);
}

void setOuterColors(cGUI::FancyRectangle& rect, cGUI::RGB color) {
	rect.cornerColor = color;
	rect.horizontalColor = color;
	rect.verticalColor = color;
}

void setRectSide(cGUI::Rectangle& rect, cGUI::Side side, bool state) {
	rect.sides[side] = state;
	drawRectangle(rect);
}

void setRectSide(cGUI::FancyRectangle& rect, cGUI::Side side, bool state) {
	rect.sides[side] = state;
	drawRectangle(rect);
}

void line(int x1, int y1, int x2, int y2, bool reset) {
	//Implement closest line algorithm
	//That takes work and I don't wanna right now, so fuck you.
}

#endif
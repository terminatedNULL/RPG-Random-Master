#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>

namespace cGUI {

	int singleCorners[] = { 218, 191, 192, 217 };
	int doubleCorners[] = { 201, 187, 200, 188 };

	struct RGB {
		int r;
		int g;
		int b;
	};

	struct Position {
		int x;
		int y;
	};

	struct Rectangle {
		int x, y;
		int width, height;
		int borderWidth;
		char borderChar;
		char fillChar;
		RGB borderColor;
		RGB fillColor;
		RGB textColor;
		std::string text;
		enum Handle textPos;
		int textX, textY;
	};

	struct FancyRectangle {
		int x, y;
		int width, height;
		int borderWidth;
		int *cornerChars;
		char horizontalChar;
		char verticalChar;
		char fillChar;
		RGB cornerColor;
		RGB horizontalColor;
		RGB verticalColor;
		RGB fillColor;
		RGB textColor;
		std::string text;
		enum Handle textPos;
		int textX, textY;

		void hover();
	};

	enum Handle {
		NO_HANDLE,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		LEFT_CENTER,
		CENTER,
		RIGHT_CENTER,
		BOTTOM_LEFT, 
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////////////////////

void cGUI::FancyRectangle::hover() {
	std::cout << "LETS GOO";
}

#endif
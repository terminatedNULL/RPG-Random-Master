#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <string>

namespace cGUI {
	struct RGB {
		int r;
		int g;
		int b;
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
	};

	struct FancyRectangle {
		int x, y;
		int width, height;
		int borderWidth;
		char cornerChars[4];
		char horizontalChar;
		char verticalChar;
		char fillChar;
		RGB cornerColor;
		RGB horizontalColor;
		RGB verticalColor;
		RGB fillColor;
		RGB textColor;
		std::string text;
		int textPos;
	};

	enum Handle {
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

#endif
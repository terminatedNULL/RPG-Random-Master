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
		int x;
		int y;
		int width;
		int height;
		char borderChar = '#';
		int borderWidth = 1;
		char fillChar = ' ';
		RGB borderColor = { 255, 255, 255 };
		RGB fillColor = { 0, 0, 0 };
		std::string text[9];
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
#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <string>

#define extern_ extern

extern_ int cursorRetX = 0;
extern_ int cursorRetY = 0;
extern_ cGUI::RGB currTextCol = { 255, 255, 255 };
extern_ cGUI::RGB currBackCol = { 0, 0, 0 };


namespace cGUI {
	typedef struct {
		int r;
		int g;
		int b;
	} RGB;

	typedef struct {
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
	} Rectangle;

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
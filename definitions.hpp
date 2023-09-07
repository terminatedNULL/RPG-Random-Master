#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>
#include <math.h>

namespace cGUI {

	int singleCorners[] = { 218, 191, 192, 217 };
	int doubleCorners[] = { 201, 187, 200, 188 };

	enum {
		DISABLED = 0,
		IDLE,
		HOVER,
		CLICK
	};

	enum {
		INNER_COLOR,
		OUTER_COLOR,
		MOD_COLOR
	};

	struct RGB {
		int r;
		int g;
		int b;

		RGB& operator +(const RGB& col) {
			(r + col.r) <= 255 ? r += col.r : r = 255;
			(g + col.g) <= 255 ? g += col.g : g = 255;
			(b + col.b) <= 255 ? b += col.b : b = 255;
			return *this;
		}
		RGB& operator -(const RGB& col) {
			(r - col.r) >= 0 ? r -= col.r : r = 0;
			(g - col.g) >= 0 ? g -= col.g : g = 0;
			(b - col.b) >= 0 ? b -= col.b : b = 0;
			return *this;
		}
		RGB& operator +(const int i) {
			(r + i) <= 255 ? r += i : r = 255;
			(g + i) <= 255 ? g += i : g = 255;
			(b + i) <= 255 ? b += i : b = 255;
			return *this;
		}
		RGB& operator -(const int i) {
			(r - i) >= 0 ? r -= i : r = 0;
			(g - i) >= 0 ? g -= i : g = 0;
			(b - i) >= 0 ? b -= i : b = 0;
			return *this;
		}
		RGB& operator *(const int i) {
			(r * i) <= 255 ? r *= i : r = 255;
			(g * i) <= 255 ? g *= i : g = 255;
			(b * i) <= 255 ? b *= i : b = 255;
			return *this;
		}
		RGB& operator /(const int i) {
			if (i == 0) { return *this; }
			(r / i) <= 255 ? r /= i : r = 255;
			(g / i) <= 255 ? g /= i : g = 255;
			(b / i) <= 255 ? b /= i : b = 255;
			return *this;
		}
	};

	RGB BLANK_RGB = { 0, 0, 0 };

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

		RGB idleColor;
		RGB hoverColor;
		RGB clickColor;

		std::string text;
		enum Handle textPos;
		int textX, textY;

		int state;
		int colorType = MOD_COLOR;
		int colorMod = 0;
		bool radio = false;
		bool radioSelect = false;
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

		RGB idleColor;
		RGB hoverColor;
		RGB clickColor;

		std::string text;
		enum Handle textPos;
		int textX, textY;
		
		int state;
		int colorType = MOD_COLOR;
		int colorMod = 0;
		bool radio = false;
		bool radioSelect = false;
	};

	enum Handle {
		NO_HANDLE = 0,
		TOP,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		LEFT,
		LEFT_CENTER,
		CENTER,
		RIGHT,
		RIGHT_CENTER,
		BOTTOM,
		BOTTOM_LEFT, 
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
}

#endif
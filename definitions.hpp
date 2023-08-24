#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define extern_ extern

extern_ int cursorRetX = 0;
extern_ int cursorRetY = 0;
extern_ RGB currTextCol = { 0, 0, 0 };

typedef struct {
	int r;
	int g;
	int b;
} RGB;

struct Rectangle {
	int width;
	int height;
	char borderChar = '#';
	int borderWidth = 1;
	char fillChar = ' ';
};

#endif
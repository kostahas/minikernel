#include "print.h"

const static size_t BUFFER_ROWS = 25;
const static size_t BUFFER_COLS = 80;

struct Char {
    volatile uint8_t character;
    volatile uint8_t color;
};

struct Char* terminalBuffer = (struct Char*) 0xb8000; // Video mem starts here.
size_t col = 0, row = 0;
uint8_t color = WHITE | BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < BUFFER_COLS; col++) {
        terminalBuffer[col + BUFFER_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < BUFFER_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < BUFFER_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < BUFFER_ROWS; row++) {
        for (size_t col = 0; col < BUFFER_COLS; col++) {
            struct Char character = terminalBuffer[col + BUFFER_COLS * row];
            terminalBuffer[col + BUFFER_COLS * (row - 1)] = character;
        }
    }

    clear_row(BUFFER_COLS - 1);
}

void print_char(char character) {
	switch (character) {
		case '\n':
			print_newline();
	}
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > BUFFER_COLS) {
        print_newline();
    }

    terminalBuffer[col + BUFFER_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

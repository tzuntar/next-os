// A simple x86 operating system kernel
// kernel.cpp - main source file
// 2019-11-16 by RedCreator37
#include "vgadef.hpp"
/*
unsigned short *terminal_buffer;
unsigned int vga_index;

void clr_scr() {
    int index = 0;
    // 25 lines by 80 columns, each element takes 2 bytes
    while (index < 80 * 25 * 2) {
        terminal_buffer[index] = ' ';
        index += 2;
    }
}

void print_str(char *str, unsigned char color) {
    int index = 0;
    while (str[index]) {
        terminal_buffer[vga_index] = (unsigned short)str[index] | (unsigned short)color << 8;
        index++;
        vga_index++;
    }
}

int main() {
    // todo: change
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_index = 0;

    clr_scr();
    print_str("Hello World! This is a custom operating system kernel, written by RedCreator37.", YELLOW);
    vga_index = 80;     // next line
    print_str("Status: ", YELLOW);
    vga_index = 89;
    print_str("OK", GREEN);
    vga_index = 160;
    print_str("Goodbye!", BRIGHT_RED);
    return 0;
}
*/


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)  {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color)  {
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str)  {
	size_t len = 0;
	while (str[len]) len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void)  {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)  {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c)  {
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
 
void terminal_write(const char* data, size_t size)  {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data)  {
	terminal_write(data, strlen(data));
}
 
int main()  {
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
    return 0;
}
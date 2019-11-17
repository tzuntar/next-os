// A simple x86 operating system kernel
// kernel.cpp - main source file
// 2019-11-16 by RedCreator37
#include "vgadef.hpp"
#include "vgautil.hpp"

// entry point
int main() {
    init_terminal();

    // print the hello world message
    terminal_color = vga_put_color(VGA_YELLOW, VGA_BLACK);
    out_string("Hello World! This is a custom operating system kernel, written by RedCreator37.\n");
    out_string("Status: ");
    terminal_color = vga_put_color(VGA_BRIGHT_GREEN, VGA_BLACK);
    out_string("OK\n");
    terminal_color = vga_put_color(VGA_BRIGHT_RED, VGA_BLACK);
    out_string("Goodbye!");

    return 0;
}

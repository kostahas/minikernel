#include "print.h"

void kernel_main() {
	print_clear();
	print_set_color(RED, BLACK);
	print_str("WELCOME TO MINIKERNEL");
}

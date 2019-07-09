#include "vga_term.h"

//Class to test cpp enviorment
class Term_t
{
public:
		Term_t()
		{
			terminal_initialize();
			terminal_writestring("Term constructed!\n");
		}
		~Term_t()
		{
			terminal_writestring("Term Destructed!\n");
		}
		write(const char* str)
		{
			terminal_writestring(str);
		}

}Console;


extern "C" void kernel_main(void)
{
  Console.write("Setting up C++ runtime enviorment\n");
	Console.write("Main running\n");
}

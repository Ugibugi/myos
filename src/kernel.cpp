#include "debug_funcs.h"
#include "interrupts.h"
#include "console.h"

//Class to test cpp enviorment

Console cout;
extern "C" void kernel_main(void)
{
	uint32_t mainptr = (uint32_t)kernel_main;
	uint64_t test_value = 0x1122334455667788;
	cout << "\n"; //reserve line for interrupt message
  cout << "Testing C++ style console\n";
	cout << ioflags::fgcolor::lightred << "Wartosc zmiennej: " << ioflags::fgcolor::green <<test_value << ioflags::fgcolor::white << "\n";
	cout << "Adres funkcji kernel_main: " << mainptr << "\n";
	debug_write("DEBUG TEST WRITE");
	test_interrupt();
}

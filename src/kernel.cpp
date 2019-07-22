#include "console.h"

//Class to test cpp enviorment
Console cout;


extern "C" void kernel_main(void)
{
	uint64_t test_value = 0x1122334455667788;
  cout << "Testing C++ style console\n";
	cout << ioflags::fgcolor::lightred << "Wartosc zmiennej: " << ioflags::fgcolor::green <<test_value << ioflags::fgcolor::white << "\n";
}

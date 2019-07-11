#include "console.h"

//Class to test cpp enviorment
Console cout;


extern "C" void kernel_main(void)
{
	int test_value = 0xBAADF00D;
  cout << "Testing C+ style console\n";
	cout << ioflags::fgcolor::lightred << "Wartosc zmiennej: " << ioflags::fgcolor::green <<test_value << ioflags::fgcolor::white << "\n";
}

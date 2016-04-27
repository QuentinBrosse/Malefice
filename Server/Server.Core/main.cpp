#include "CMain.h"

CMain	*pMain = NULL;

int main(int argc, char * argv[])
{
	pMain = new CMain("Test", 1234);

	if (pMain->Init() == false)
	{
#ifdef _WIN32
		TerminateProcess(GetCurrentProcess(), 0);
#else
		_exit(42);
#endif
	}

	while (pMain->IsActive())
	{
		pMain->Pulse();
	}

	return (0);
}
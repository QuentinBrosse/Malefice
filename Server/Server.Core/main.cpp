#include "ServerCore.h"

int main(int argc, char * argv[])
{
	ServerCore& serverCore = ServerCore::getInstance();

	if (serverCore.Init() == false)
		return EXIT_FAILURE;

	while (serverCore.IsActive())
	{
		serverCore.Pulse();
	}
	return EXIT_SUCCESS;
}
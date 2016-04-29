#include "ServerCore.h"

int main(int argc, char* argv[])
{
	ServerCore& serverCore = ServerCore::getInstance();

	if (serverCore.init() == false)
	{
		std::cerr << "Server initialization failed. Exiting." << std::endl;
		return EXIT_FAILURE;
	}
	while (serverCore.isActive())
	{
		serverCore.pulse();
	}
	return EXIT_SUCCESS;
}

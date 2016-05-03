#include "ServerCore.h"
#include "ProjectGlobals.h"

int main(int argc, char* argv[])
{
	ServerCore::getInstance().run();
	return EXIT_SUCCESS;
}

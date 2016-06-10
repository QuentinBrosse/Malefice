#include <cstdlib>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	Logger::getInstance().setup(ProjectGlobals::getGameServerLogFilepath());
	ServerCore::getInstance().run();
	return EXIT_SUCCESS;
}

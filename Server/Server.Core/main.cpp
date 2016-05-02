#include "ServerCore.h"
#include "LoggerSetup.h"
#include "ProjectGlobals.h"

int main(int argc, char* argv[])
{
	Logger::setup(argc, argv, ProjectGlobals::GAME_SERVER_LOG_FILEPATH);
	ServerCore::getInstance().run();
	return EXIT_SUCCESS;
}

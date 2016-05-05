#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	Logger::getInstance().setup(ProjectGlobals::GAME_SERVER_LOG_FILEPATH);
	ServerCore::getInstance().run();
	return EXIT_SUCCESS;
}

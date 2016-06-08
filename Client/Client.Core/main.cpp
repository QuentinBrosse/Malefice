#include <cstdlib>
#include "ClientCore.h"
#include "ProjectGlobals.h"
#include "Logger.h"
#include "ressource.h"

int main(int argc, char* argv[])
{
	Logger::getInstance().setup(ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH);
	ClientCore::getInstance().run();
	return EXIT_SUCCESS;
}

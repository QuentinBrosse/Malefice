#include "ServerCore.h"
#include "Logger.h"


void	configureLogger();

int main(int argc, char* argv[])
{
	START_EASYLOGGINGPP(argc, argv);
	configureLogger();
	ServerCore& serverCore = ServerCore::getInstance();

	LOG(INFO) << "Hello, test!";
	getchar();
	return 0;

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

static void	configureLogger()
{
	el::Configurations	defaultLoggerConf;

	defaultLoggerConf.setToDefault();
	defaultLoggerConf.setGlobally(el::ConfigurationType::Format, "[%datetime{%d/%M/%Y %H:%m:%s}] %level- %msg (logged at %fbase:%line by %func in thread %thread)");
	defaultLoggerConf.setGlobally(el::ConfigurationType::Filename, "Server.Core.log");
	el::Loggers::reconfigureLogger("default", defaultLoggerConf);
}

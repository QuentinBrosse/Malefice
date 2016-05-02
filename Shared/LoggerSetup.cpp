#include "LoggerSetup.h"

INITIALIZE_EASYLOGGINGPP

void	Logger::setup(int argc, char* argv[], const std::string& filepath)
{
	START_EASYLOGGINGPP(argc, argv);
	el::Configurations	defaultLoggerConf;

	defaultLoggerConf.setToDefault();
	defaultLoggerConf.setGlobally(el::ConfigurationType::Format, "[%datetime{%d/%M/%Y %H:%m:%s}] %level- %msg (logged at %fbase:%line by %func in thread %thread)");
	defaultLoggerConf.setGlobally(el::ConfigurationType::Filename, filepath);
	defaultLoggerConf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
	el::Loggers::reconfigureLogger("default", defaultLoggerConf);
	el::Loggers::setDefaultConfigurations(defaultLoggerConf, true);
}

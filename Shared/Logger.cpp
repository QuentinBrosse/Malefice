#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <spdlog/spdlog.h>
#include "Logger.h"
#include "ProjectGlobals.h"

const std::string	Logger::LOGGER_NAME		= ProjectGlobals::GAME_NAME + "Logger";
const std::size_t	Logger::MAX_FILE_SIZE	= 1024 * 1024 * 10;
const std::size_t	Logger::MAX_FILE_NB		= 10;

void	Logger::setup(const std::string& filePath)
{
	std::vector<spdlog::sink_ptr>	sinks;
	std::size_t						extPos = filePath.find_last_of('.');

	sinks.push_back(std::make_shared<spdlog::sinks::stderr_sink_st>());
	sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_st>(filePath.substr(0, extPos), filePath.substr(extPos + 1), Logger::MAX_FILE_SIZE, Logger::MAX_FILE_NB, true));
	m_logger = std::make_shared<spdlog::logger>(Logger::LOGGER_NAME, begin(sinks), end(sinks));

	spdlog::register_logger(m_logger);
	spdlog::set_pattern("[%d/%m/%Y %H:%M:%S] %l %v");
}

spdlog::details::line_logger	Logger::log(LogLevel logLevel, LogCategory logCategory)
{
	switch (logLevel)
	{
	case LogLevel::Trace:
		return m_logger->trace();
		break;
	case LogLevel::Debug:
		return m_logger->debug();
		break;
	case LogLevel::Info:
		return m_logger->info();
		break;
	case LogLevel::Warning:
		return m_logger->warn();
		break;
	case LogLevel::Error:
		return m_logger->error();
		break;
	case LogLevel::Critical:
	default:
		return m_logger->critical();
		break;
	}
}

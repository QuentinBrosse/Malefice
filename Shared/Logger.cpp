#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <spdlog/spdlog.h>
#include "Logger.h"
#include "ProjectGlobals.h"
#include "Utility.h"

const std::string	Logger::LOGGER_NAME		= ProjectGlobals::GAME_NAME + "Logger";
const std::size_t	Logger::MAX_FILE_SIZE	= 1024 * 1024 * 10;
const std::size_t	Logger::MAX_FILE_NB		= 10;

void	Logger::setup(const std::string& filePath)
{
	std::vector<spdlog::sink_ptr>	sinks;
	std::size_t						extPos = filePath.find_last_of('.');
	std::string						filePathPid = filePath;

	filePathPid.insert(extPos, "." + std::to_string(utility::getPid()));
	extPos = filePathPid.find_last_of('.');
	sinks.push_back(std::make_shared<spdlog::sinks::stderr_sink_st>());
	sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_st>(filePathPid.substr(0, extPos), filePathPid.substr(extPos + 1), Logger::MAX_FILE_SIZE, Logger::MAX_FILE_NB, true));

	m_logger = std::make_shared<spdlog::logger>(Logger::LOGGER_NAME, begin(sinks), end(sinks));

	spdlog::register_logger(m_logger);
	spdlog::set_pattern("[%d/%m/%Y %H:%M:%S][%l]%v");
}

std::string	Logger::logCategoryToString(Logger::LogCategory logCategory)
{
	switch (logCategory)
	{
	case LogCategory::GENERAL:
		return "general";
		break;
	case LogCategory::NETWORK:
		return "network";
		break;
	case LogCategory::CHAT:
		return "chat";
		break;
	default:
		throw std::invalid_argument("Unknown Logger::LogCategory " + std::to_string(static_cast<int>(logCategory)));
		break;
	}
}


Logger::LogLine::LogLine(Logger::LogLevel logLevel, Logger::LogCategory logCategory) :
	m_lineLogger(LogLine::getLogger(logLevel))
{
	m_lineLogger << "[" << Logger::logCategoryToString(logCategory) << "] ";
}

spdlog::details::line_logger	Logger::LogLine::getLogger(Logger::LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::Trace:
		return Logger::getInstance().m_logger->trace();
		break;
	case LogLevel::Debug:
		return Logger::getInstance().m_logger->debug();
		break;
	case LogLevel::Info:
		return Logger::getInstance().m_logger->info();
		break;
	case LogLevel::Warning:
		return Logger::getInstance().m_logger->warn();
		break;
	case LogLevel::Error:
		return Logger::getInstance().m_logger->error();
		break;
	case LogLevel::Critical:
		return Logger::getInstance().m_logger->critical();
		break;
	default:
		throw std::invalid_argument("Unknown Logger::LogLevel " + std::to_string(static_cast<int>(logLevel)));
	}
}

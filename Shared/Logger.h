#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include "Singleton.h"
#include "Export.h"

#define LOG_TRACE(logCategory)		Logger::getInstance().log(Logger::LogLevel::Trace, Logger::LogCategory::logCategory)
#define LOG_DEBUG(logCategory)		Logger::getInstance().log(Logger::LogLevel::Debug, Logger::LogCategory::logCategory)
#define LOG_INFO(logCategory)		Logger::getInstance().log(Logger::LogLevel::Info, Logger::LogCategory::logCategory)
#define LOG_WARNING(logCategory)	Logger::getInstance().log(Logger::LogLevel::Warning, Logger::LogCategory::logCategory)
#define LOG_ERROR(logCategory)		Logger::getInstance().log(Logger::LogLevel::Error, Logger::LogCategory::logCategory)
#define LOG_CRITICAL(logCategory)	Logger::getInstance().log(Logger::LogLevel::Critical, Logger::LogCategory::logCategory)

class MALEFICE_DLL_EXPORT Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

public:
	enum class LogLevel : int
	{
		Trace,
		Debug,
		Info,
		Warning,
		Error,
 		Critical,
		LevelCount
	};

	enum class LogCategory : int
	{
		GENERAL,
		NETWORK,
		CHAT,
		PLAYER,
		CategoryCount
	};

	void							setup(const std::string& filePath);
	spdlog::details::line_logger	log(LogLevel logLevel, LogCategory logCategory);


protected:
	Logger()	= default;
	~Logger()	= default;


private:
	static const std::string	LOGGER_NAME;
	static const std::size_t	MAX_FILE_SIZE;
	static const std::size_t	MAX_FILE_NB;

	std::shared_ptr<spdlog::logger>	m_logger;
};

#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include "Singleton.h"
#include "Export.h"

#define LOG_TRACE		Logger::getInstance().log(Logger::LogLevel::Trace)
#define LOG_DEBUG		Logger::getInstance().log(Logger::LogLevel::Debug)
#define LOG_INFO		Logger::getInstance().log(Logger::LogLevel::Info)
#define LOG_WARNING		Logger::getInstance().log(Logger::LogLevel::Warning)
#define LOG_ERROR		Logger::getInstance().log(Logger::LogLevel::Error)
#define LOG_CRITICAL	Logger::getInstance().log(Logger::LogLevel::Critical)

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

	void							setup(const std::string& filePath);
	spdlog::details::line_logger	log(LogLevel logLevel);


protected:
	Logger()	= default;
	~Logger()	= default;


private:
	static const std::string	LOGGER_NAME;
	static const std::size_t	MAX_FILE_SIZE;
	static const std::size_t	MAX_FILE_NB;

	std::shared_ptr<spdlog::logger>	m_logger;
};

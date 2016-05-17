#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include "Singleton.h"
#include "Export.h"

#define LOG_TRACE(logCategory)		(Logger::LogLine(Logger::LogLevel::Trace, Logger::LogCategory::logCategory))
#define LOG_DEBUG(logCategory)		(Logger::LogLine(Logger::LogLevel::Debug, Logger::LogCategory::logCategory))
#define LOG_INFO(logCategory)		(Logger::LogLine(Logger::LogLevel::Info, Logger::LogCategory::logCategory))
#define LOG_WARNING(logCategory)	(Logger::LogLine(Logger::LogLevel::Warning, Logger::LogCategory::logCategory))
#define LOG_ERROR(logCategory)		(Logger::LogLine(Logger::LogLevel::Error, Logger::LogCategory::logCategory))
#define LOG_CRITICAL(logCategory)	(Logger::LogLine(Logger::LogLevel::Critical, Logger::LogCategory::logCategory))

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
		ECS,
		CategoryCount
	};

	class MALEFICE_DLL_EXPORT LogLine
	{
	public:
		LogLine(Logger::LogLevel logLevel, Logger::LogCategory logCategory);
		LogLine(const LogLine& logLine)	= delete;
		~LogLine()						= default;

		template<class T>
		LogLine&	operator<<(const T& what)
		{
			m_lineLogger << what;
			return *this;
		}


	private:
		static spdlog::details::line_logger	getLogger(Logger::LogLevel logLevel);

		spdlog::details::line_logger	m_lineLogger;
	};
	friend class LogLine;

	void							setup(const std::string& filePath);
	

protected:
	Logger();
	~Logger()	= default;


private:
	static const std::string	LOGGER_NAME;
	static const std::size_t	MAX_FILE_SIZE;
	static const std::size_t	MAX_FILE_NB;

	static std::string	logCategoryToString(Logger::LogCategory logCategory);


	std::shared_ptr<spdlog::logger>	m_logger;
};

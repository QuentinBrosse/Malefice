#include <sstream>
#include <chrono>
#include "TimeUtility.h"
#include "StringUtility.h"

long long	utility::TimeUtility::getMsTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string	utility::TimeUtility::getElapsedTimeSince(long long msTime)
{
	std::ostringstream	oss;
	long long			elapsedSeconds = ((utility::TimeUtility::getMsTime() - msTime) / 1000ll);
	long long			seconds = (elapsedSeconds % 60ll);
	long long			elapsedMinutes = (elapsedSeconds / 60ll);
	long long			minutes = (elapsedMinutes % 60ll);
	long long			elapsedHours = (elapsedMinutes / 60ll);
	long long			hours = (elapsedHours % 60ll);
	long long			elapsedDays = (elapsedHours / 24ll);
	long long			days = (elapsedDays % 24ll);

	oss << days << utility::StringUtility::pluralize(" day", days) << ", "
		<< hours << utility::StringUtility::pluralize(" hour", hours) << ", "
		<< minutes << utility::StringUtility::pluralize(" minute", minutes) << ", "
		<< seconds << utility::StringUtility::pluralize(" second", seconds);
	return oss.str();
}

long long utility::TimeUtility::msToSec(long long sec)
{
	return sec * 1000;
}
#include <sstream>
#include <chrono>
#include <Windows.h>
#include <tchar.h>
#include "Utilities.h"

DWORD	Utilities::getSerial()
{
#ifdef _WIN32
	DWORD dwSerial;
	GetVolumeInformation(_T("C:\\"), nullptr, 0, &dwSerial, nullptr, nullptr, nullptr, 0);

	return dwSerial;
#else
	throw std::logic_error("Utilities::getSerial() not implemented");
#endif
}

std::string	Utilities::getSerialHash()
{
	DWORD dwSerial = Utilities::getSerial();
	char szSerialMask[] = "0000-0000";
	int i = 8;

	while (dwSerial > 0 && i >= 0)
	{
		int v = (dwSerial & 0xF);
		char ch = (v < 10) ? '0' + v : 'A' + (v + 10);
		szSerialMask[i--] = ch;
		if (i == 4)
			i--;
		dwSerial >>= 4;
	}
	return std::string(szSerialMask);
}

long long	Utilities::getMsTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string	Utilities::getElapsedTimeSince(long long msTime)
{
	std::ostringstream	oss;
	long long			elapsedSeconds = ((Utilities::getMsTime() - msTime) / 1000ll);
	long long			seconds = (elapsedSeconds % 60ll);
	long long			elapsedMinutes = (elapsedSeconds / 60ll);
	long long			minutes = (elapsedMinutes % 60ll);
	long long			elapsedHours = (elapsedMinutes / 60ll);
	long long			hours = (elapsedHours % 60ll);
	long long			elapsedDays = (elapsedHours / 24ll);
	long long			days = (elapsedDays % 24ll);

	oss << days << pluralize(" day", days) << ", " << hours << pluralize(" hour", hours) << ", " << minutes << pluralize(" minute", minutes) << ", " << seconds << pluralize(" second", seconds);
	return oss.str();
}

template<class T>
std::string	Utilities::pluralize(const std::string& word, const T& nb)
{
	if (nb > -2 && nb < 2)
		return word;
	return word + "s";
}
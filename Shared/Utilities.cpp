#include "Utilities.h"

DWORD Utilities::GetSerial()
{
	DWORD dwSerial;
	GetVolumeInformation(_T("C:\\"), nullptr, 0, &dwSerial, nullptr, nullptr, nullptr, 0);

	return dwSerial;
}

std::string Utilities::GetSerialHash()
{
	DWORD dwSerial = Utilities::GetSerial();

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

unsigned long Utilities::GetTime()
{
#ifdef _WIN32
	return timeGetTime();
#else
	timeval ts;
	gettimeofday(&ts, 0);
	return (DWORD)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
#endif
}

std::string Utilities::FormatString(const std::string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2;
	std::string str;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (1) {
		formatted.reset(new char[n]);
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return std::string(formatted.get());
}

std::string	Utilities::GetTimePassedFromTime(unsigned long time)
{
	int secondsPassed = ((GetTime() - time) / 1000);
	int seconds = (secondsPassed % 60);
	int minutesPassed = (secondsPassed / 60);
	int minutes = (minutesPassed % 60);
	int hoursPassed = (minutesPassed / 60);
	int hours = (hoursPassed % 60);
	int daysPassed = (hoursPassed / 24);
	int days = (daysPassed % 24);
	return FormatString("%d day(s), %d hour(s), %d minute(s) and %d second(s)", days, hours, minutes, seconds);
}

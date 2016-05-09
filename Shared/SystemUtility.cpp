#ifdef _WIN32
#include <tchar.h>
#else
#include <unistd.h>
#endif
#include "SystemUtility.h"

DWORD	utility::SystemUtility::getSerial()
{
#ifdef _WIN32
	DWORD dwSerial;
	GetVolumeInformation(_T("C:\\"), nullptr, 0, &dwSerial, nullptr, nullptr, nullptr, 0);

	return dwSerial;
#else
	throw std::logic_error("utility::getSerial() not implemented");
#endif
}

std::string	utility::SystemUtility::getSerialHash()
{
	DWORD	dwSerial = utility::SystemUtility::getSerial();
	char	szSerialMask[] = "0000-0000";
	int		i = 8;

	while (dwSerial > 0 && i >= 0)
	{
		int		v = (dwSerial & 0xF);
		char	ch = (v < 10) ? '0' + v : 'A' + (v + 10);

		szSerialMask[i--] = ch;
		if (i == 4)
			i--;
		dwSerial >>= 4;
	}
	return std::string(szSerialMask);
}


pid_t	utility::SystemUtility::getPid()
{
#ifdef _WIN32
	return GetCurrentProcessId();
#else
	return getpid();
#endif
}

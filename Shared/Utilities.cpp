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
#pragma once

#include	<vector>

#include	<TCPInterface.h>
#include	<RakSleep.h>
#include	<RakString.h>

#include	"Singleton.h"

#include	"TimeUtility.h"

class MasterList : public Singleton<MasterList>
{
	friend class Singleton<MasterList>;

public:
	MasterList();
	~MasterList();

	std::vector<std::string> fetch();

private:
	RakNet::TCPInterface*	m_tcp;
	long long				m_lastUpdateTime;
};
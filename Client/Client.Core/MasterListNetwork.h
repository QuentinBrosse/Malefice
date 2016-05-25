#pragma once

#include <TCPInterface.h>
#include <RakSleep.h>
#include <RakString.h>
#include <vector>
#include <iostream>

#include "Singleton.h"
#include "TimeUtility.h"

class MasterListNetwork : public Singleton<MasterListNetwork>
{
	friend class Singleton<MasterListNetwork>;
public:
	MasterListNetwork();
	~MasterListNetwork();
	std::vector<std::string> fetch();
private:
	RakNet::TCPInterface*	m_tcp;
	long long				m_lastUpdateTime;
};
#pragma once

#include	<thread>
#include	<string>

#include	<TCPInterface.h>
#include	<RakSleep.h>
#include	<RakString.h>

#include	"Singleton.h"

enum masterListState
{
	STATE_ADD,
	STATE_UPDATE,
	STATE_DELETE
};

class MasterList : public Singleton<MasterList>
{
	friend class Singleton<MasterList>;

public:
	MasterList();
	~MasterList();

	void	run();

	void	pulse();

private:
	RakNet::TCPInterface*	m_tcp;
	std::thread				m_worker;

	masterListState			m_state;
	long long				m_lastUpdateTime;
	std::string				m_token;
};
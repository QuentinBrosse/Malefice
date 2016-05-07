#pragma once

#ifdef _WIN32
#include	<windows.h>
#else
#include	<pthread.h>
#endif

#include "Export.h"

#define	USE_CRITICAL_SECTION

class MALEFICE_DLL_EXPORT Mutex
{

private:

#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	CRITICAL_SECTION 	m_criticalSection;
#else
	HANDLE 				m_hMutex;
#endif
#else
	pthread_mutex_t 	m_mutex;
#endif
	int 				m_lockCount;

public:

	Mutex();
	~Mutex();

	void	lock();
	bool	tryLock(unsigned int timeout);
	void	unlock();

};
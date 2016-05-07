#pragma once

#ifdef _LINUX
#include <pthread.h>
#endif

#include "Mutex.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT Thread
{

private:

	typedef void(*ThreadFunction_t)(Thread * creator);

#ifdef _WIN32
	HANDLE					m_hThread;
#else
	pthread_t				m_thread;
#endif
	ThreadFunction_t		m_pfnThreadFunction;
	Mutex					m_startedMutex;
	bool					m_started;
	Mutex					m_runningMutex;
	bool					m_running;
	Mutex					m_userDataMutex;
	void					* m_pUserData;

	void					setStarted(bool bStarted);
	bool					isStarted();

	void					setRunning(bool bRunning);

public:

	Thread();
	~Thread();

	void        start(ThreadFunction_t pfnThreadFunction, bool waitForStart = true);
	bool        stop(bool waitForExit = true, bool terminate = false);
	bool        isRunning();

	template <typename DataType>
	void        setUserData(DataType pUserData)
	{
		m_userDataMutex.lock();
		m_pUserData = (void *)pUserData;
		m_userDataMutex.unlock();
	}

	template <typename ReturnType>
	ReturnType  getUserData()
	{
		m_userDataMutex.lock();
#ifdef _MSC_VER
#pragma warning(disable:4800) // forcing value to bool (performance warning)
#endif
		ReturnType userData = (ReturnType)m_pUserData;
		m_userDataMutex.unlock();
		return userData;
	}

#ifdef _WIN32
	static void startAddress(Thread * pThis);
#else
	static void * startAddress(void * pThis);
#endif

};
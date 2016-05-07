#ifdef _WIN32
#include	<windows.h>
#endif
#include	"Mutex.h"

#include	"Utilities.h"

Mutex::Mutex()
{
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	InitializeCriticalSection(&m_criticalSection);
#else
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
#endif
#else
	pthread_mutex_init(&m_mutex, NULL);
#endif
	m_lockCount = 0;
}

Mutex::~Mutex()
{
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	DeleteCriticalSection(&m_criticalSection);
#else
	CloseHandle(m_hMutex);
#endif
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

void Mutex::lock()
{
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	EnterCriticalSection(&m_criticalSection);
#else
	WaitForSingleObject(m_hMutex, INFINITE);
#endif
#else
	pthread_mutex_lock(&m_mutex);
#endif
	m_lockCount++;
}

bool Mutex::tryLock(unsigned int timeout)
{
	bool locked = false;

#if defined(_WIN32) && !defined(USE_CRITICAL_SECTION)
	locked = (WaitForSingleObject(m_hMutex, uiTimeout) == 0);
#else
	if (timeout == 0)
	{
#ifdef _WIN32
		locked = (TryEnterCriticalSection(&m_criticalSection) != 0);
#else
		locked = pthread_mutex_trylock(&m_mutex);
#endif
	}
	else
	{
		unsigned long ulEndTime = (Utilities::GetTime() + timeout);
		while (Utilities::GetTime() < ulEndTime)
		{
#ifdef _WIN32
			if (TryEnterCriticalSection(&m_criticalSection))
#else
			if (pthread_mutex_trylock(&m_mutex))
#endif
			{
				locked = true;
				break;
			}
		}
	}
#endif
	if (locked)
	{
		m_lockCount++;
	}

	return locked;
}

void Mutex::unlock()
{
	m_lockCount--;

#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	LeaveCriticalSection(&m_criticalSection);
#else
	ReleaseMutex(m_hMutex);
#endif
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}
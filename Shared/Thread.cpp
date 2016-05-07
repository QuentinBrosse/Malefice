#include "Thread.h"

#ifndef _WIN32
#include <unistd.h>
#include <pthread.h>
#define Sleep usleep
#endif

Thread::Thread() : 
	m_started(false), m_running(false), m_pUserData(nullptr)
{
}

Thread::~Thread()
{
	stop();
}

void Thread::start(ThreadFunction_t pfnThreadFunction, bool waitForStart)
{
	stop();

	m_pfnThreadFunction = pfnThreadFunction;
	m_started = false;
	m_running = false;

#ifdef _WIN32
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startAddress, (void *)this, 0, NULL);
#else
	pthread_create(&m_thread, NULL, StartAddress, (void *)this);
#endif

	if (waitForStart)
	{
		while (!isStarted())
		{
			Sleep(1);
		}
	}
}

bool Thread::stop(bool waitForExit, bool terminate)
{
	if (isStarted())
	{
		if (terminate)
		{
#ifdef _WIN32
			TerminateThread(m_hThread, 0);
#else
			pthread_cancel(m_thread);
#endif
		}
#ifdef _WIN32
		CloseHandle(m_hThread);
#else
		pthread_cancel(m_thread);
#endif
		if (!terminate && waitForExit)
		{
			while (isRunning())
			{
				Sleep(1);
			}
		}

		setRunning(false);
		setStarted(false);

#ifdef _WIN32
		m_hThread = nullptr;
#else
		m_thread = nullptr;
#endif
		return true;
	}
	return false;
}

void Thread::setStarted(bool started)
{
	m_startedMutex.lock();
	m_started = started;
	m_startedMutex.unlock();
}

bool Thread::isStarted()
{
	m_startedMutex.lock();
	bool started = m_started;
	m_startedMutex.unlock();

	return started;
}

void Thread::setRunning(bool running)
{
	m_runningMutex.lock();
	m_running = running;
	m_runningMutex.unlock();
}

bool Thread::isRunning()
{
	m_runningMutex.lock();
	bool running = m_running;
	m_runningMutex.unlock();

	return running;
}

#ifdef _WIN32
void Thread::startAddress(Thread * pThis)
#else
void * Thread::startAddress(void * pVoidThis)
#endif
{
#ifndef _WIN32
	Thread * pThis = (Thread *)pVoidThis;
#endif
	pThis->setStarted(true);
	pThis->setRunning(true);
	pThis->m_pfnThreadFunction(pThis);
	pThis->setRunning(false);

#ifndef _WIN32
	return (void *)1;
#endif
}
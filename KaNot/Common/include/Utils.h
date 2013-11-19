#pragma once
#ifndef UTILS_H
#define	UTILS_H

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __ANDROID__
#include <sys/time.h>
#endif

namespace Scioto
{
	class Timer
	{
	public:
		Timer(); //initializes Timer class
		void Reset();
		const long double GetDeltaTime();
		const long double Update(); // updates current time
		const long double GetMemTime() const; // returns time of last Update() event
		const long double GetCurTime(); // returns time elapsed since program start

	private:
		long double m_startTime;
		long double m_memTime;
		long double m_curTime;
		
#ifdef _WIN32
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_startCount;
		LARGE_INTEGER m_curCount;
#endif

#ifdef __ANDROID__
		timeval m_startCount;
		timeval m_curCount
#endif
	};

	class Util
	{
	public:
	};
}

#endif
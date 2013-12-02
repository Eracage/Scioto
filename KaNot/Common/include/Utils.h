#pragma once
#ifndef UTILS_H_SCIOTO
#define UTILS_H_SCIOTO

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
		/**
		Sets timer start and memtime to current time
		*/
		void Reset();
		/**
		Updates memtime, returns the difference
		*/
		const long double GetDeltaTime();
		/**
		Updates memtime
		*/
		const long double Update();
		/**
		Returns time elapsed since timer start
		*/
		const long double GetCurTime();
		/**
		Returns time of last Update() event
		*/
		const long double GetMemTime() const;

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
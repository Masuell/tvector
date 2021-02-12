#ifndef __SUPPORT_H__
#define __SUPPORT_H__
/** \file main_support.h
 *  \brief Soubor pro multiplatformní podporu programu v různých OS
 *  \author Petyovský
 *  \version 2021
 *  $Id: main_support.h 1023 2021-02-08 09:42:15Z petyovsky $
 */
 
static inline double difftimespec(struct timespec aEnd, struct timespec aBegin)
	{
	return difftime(aEnd.tv_sec, aBegin.tv_sec) + (((long long) aEnd.tv_nsec - aBegin.tv_nsec) / 1000000000.0);
	}

#ifdef __MACH__ // Detect macOS
	#include <Availability.h>
	#if __MAC_OS_X_VERSION_MIN_REQUIRED < 101500 // macOS < 10.15 (pre Catalina) does not have timespec_get, use clock_get_time
		#include <mach/clock.h>
		#include <mach/mach.h>

		#define TIME_UTC 1
		static inline int timespec_get(struct timespec *ts, int unused)
			{
			clock_serv_t cclock;
			mach_timespec_t mts;
			host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
			clock_get_time(cclock, &mts);
			mach_port_deallocate(mach_task_self(), cclock);
			ts->tv_sec = mts.tv_sec;
			ts->tv_nsec = mts.tv_nsec;
			return unused;
			}
	#endif // __MAC_OS_X_VERSION_MIN_REQUIRED
#endif // __MACH__

#endif /* __SUPPORT_H__*/

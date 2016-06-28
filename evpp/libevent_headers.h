/********************************************************************
 *	Created:	2014/03/06 14:19
 *	File name: 	libevent_headers.h
 *	Author:		weizili
 *	Purpose:	
 *
 *	Copyright 2010-2013, All Rights Reserved.
 ********************************************************************/
#pragma once

#ifdef WIN32
	#include <WinSock2.h>
	#include <event/event.h>
	#include <event/evhttp.h>
    #include <event/evutil.h>
    #include <event/evdns.h>
    //#include <event/compat/sys/queue.h>
    #define _LIBEVENT14 1
#else
	#include <sys/queue.h>
    #ifdef _LIBEVENT14
        #include <event.h>
        #include <evhttp.h>
        #include <event/evutil.h>
        #include <event/evdns.h>
    #else
        #include <event2/event.h>
        #include <event2/event_struct.h>
        #include <event2/buffer.h>
        #include <event2/bufferevent.h>
        #include <event2/http.h>
        #include <event2/http_compat.h>
        #include <event2/http_struct.h>
        #include <event2/event_compat.h>
        #include <event2/dns.h>
        #include <event2/dns_compat.h>
        #include <event2/dns_struct.h>
	#endif
#endif

#ifndef evtimer_new
#define evtimer_new(b, cb, arg)	       event_new((b), -1, 0, (cb), (arg))
#endif

#ifdef _LIBEVENT14
extern "C" {
    struct event * event_new(struct event_base *base, int fd, short events, void(*cb)(int, short, void *), void *arg);
    void event_free(struct event *ev);
}

// There is a bug of event timer for libevent1.4 on windows platform.
//   libevent1.4 use '#define evtimer_set(ev, cb, arg)  event_set(ev, -1, 0, cb, arg)' to assign a timer,
//   but '#define event_initialized(ev) ((ev)->ev_flags & EVLIST_INIT && (ev)->ev_fd != (int)INVALID_HANDLE_VALUE)'
//   So, if we use a event timer on windows, event_initialized(ev) will never return true.
#ifdef event_initialized
#undef event_initialized
#endif
#define event_initialized(ev) ((ev)->ev_flags & EVLIST_INIT)


#endif

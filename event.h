#ifndef _EVENT_H_
#define _EVENT_H_

#define FD_READ 0x1
#define FD_WRITE 0x2
#define FD_EXCEPTION 0x3

/**
 * signal type
 */
typedef int sig_t;

/** callback types */

/**
 * sig_func_t - signal callback
 * @sig_t:	the signal on which the callback was registered
 * @o:		private context for the callback
 *
 * callback to execute upon recieving a signal the task has on
 */
typedef void (*sig_func_t)(sig_t s, void *o);

/**
 * fd_func_t - file descriptor callback
 * @fd:		file descriptor for which this callback was called
 * @o:		private context for the callback
 *
 * callback to execute upon recieving input on a file descriptor the task has
 * registered on.
 */
typedef void (*fd_func_t)(int fd, void *o);

/**
 * event_func_t - event callback
 * @o:		private context for the callback
 *
 * callback to execute upon recieving input on a file descriptor the task has
 * registered on.
 */
typedef void (*event_func_t)(void *o);

/** signal api */

/**
 * signal_register - register a task to be notified upon recieving a signal
 * @signal:	the signal on which to register the task
 * @func:	callback function to execute on behalf of the task upon
 * 		recieving the signal
 * @data:	task context for the callback function
 */
int signal_register(sig_t signal, sig_func_t func, void *data);

/**
 *signal_set - set a signal for notifying all registered tasks
 *@signal:	the signal to set
 */
void signal_set(sig_t signal);

/** file descriptor api */

/**
 * fd_add - register a file descriptor for input notification
 * @fd:		the file descriptor to monitor
 * @type:	read/write/exception
 * @func:	callback function to execute on behalf of the task upon
 * 		recieving input on this file descriptor
 * @data:	task context data for the callback function
 */
int fd_add(int fd, int type, fd_func_t func, void *data);

/**
 * fd_del - unregister a file descriptor for input notification
 * @fd:		the file descriptor to unregister
 * @type:	read/write/exception
 * @func:	callback function executed when the file descriptor was being
 * 		monitored. This is used for fully identifying the file
 * 		descriptor to unregister
 * @data:	task context data for the callback function
 */
void fd_del(int fd, int type, fd_func_t func, void *data);

/** event api */

/**
 * event_add - add an event to the event loop to be executed later
 * @func:	callback function executed when the event gets handled
 * @data:	task context data for the callback function
 */
int event_add(event_func_t func, void *data);

/**
 * event_add_once - add an event to the event loop only if there is none in
 * 		    the list already with the same callback function and data
 * @func:	callback function to match
 * @data:	task context data to match
 */
int event_add_once(event_func_t func, void *data);

/**
 * event_del_once - delete the first event containing the matched data from the
 * 		    event loop
 * @data:	task context data to match
 */
void event_del_once(void *data);

/**
 * event_del_all - delete all events containing the matched data from the
 * 		   event loop
 * @data:	task context data to match
 */
void event_del_all(void *data);

/**
 * event_init - initialize the event loop
 * @sc:		signal count
 */
int event_init(int sc);

/**
 * event_uninit - uninitialize the event loop
 */
void event_uninit(void);

/**
 * event_loop - start executing the event loop
 *
 * the event loop runs until there are no events left to execute
 */
int event_loop(void);

#endif


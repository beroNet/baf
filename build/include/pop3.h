/* libpop3 0.5 -:-  (C)opyright 2001 - 2004 Kristian Van Der Vliet
/
/  This library is free software; you can redistribute it and/or
/  modify it under the terms of the GNU Library General Public
/  License as published by the Free Software Foundation; either
/  version 2 of the License, or (at your option) any later version.
/
/  This library is distributed in the hope that it will be useful,
/  but WITHOUT ANY WARRANTY; without even the implied warranty of
/  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
/  Library General Public License for more details.
/
/  You should have received a copy of the GNU Library General Public
/  License along with this library; if not, write to the Free
/  Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
/  MA 02111-1307, USA
*/

#ifndef __POP3_LIBPOP3_H_
#define __POP3_LIBPOP3_H_ 1

#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define POP3_DEFAULT_PORT	110
#define POP3_DEFAULT_TIMEOUT	60	// One minute

#define POP3_BUFFER_SIZE	4096	// 4k input buffer

typedef enum _pop3_state_t {
	POP3_NEW		= 0x00,
	POP3_CONNECTED		= 0x01,
	POP3_NOTCONNECTED	= 0x02,
	POP3_TIME		= 0x04,
} pop3_state_t;

typedef struct _pop3_session_t {
	char			*server;		// Server URI
	unsigned int		port;			// Port number
	time_t			timeout;		// Maximum time allowed for socket operations
	unsigned int		flags;			// Various connection & control flags
	int			sock_fd;		// fd for server connection
	struct sockaddr_in	addr;			// Socket connection details
	struct hostent		*host;			// Host details
	char			*buffer;		// Input buffer
	pop3_state_t		status;			// Current connection/error status
	struct sigaction	old_sigaction;		// Data returned by sigaction(), restored by smtp_destroy_session()
} pop3_session_t;


pop3_session_t *pop3_create_session (const char *server, const unsigned int port, const time_t timeout, const unsigned int flags);
int pop3_destroy_session (pop3_session_t *s);
int pop3_connect (pop3_session_t *s, const char *user, const char *pass);
int pop3_disconnect (pop3_session_t *s);

const char *pop3_get_server (const pop3_session_t *s);
int pop3_set_server (pop3_session_t *s, const char *server);
int pop3_get_port (const pop3_session_t *s);
int pop3_set_port (pop3_session_t *s, const int port);
time_t pop3_get_timeout (const pop3_session_t *s);
int pop3_set_timeout (pop3_session_t *s, const time_t timeout);
unsigned int pop3_get_flags (const pop3_session_t *s);
int pop3_set_flags (pop3_session_t *s, const unsigned int flags);

int pop3_get_message_count (pop3_session_t *s, int *msg_cnt, int *mbox_siz);
int pop3_get_message_size (pop3_session_t *s, const unsigned int msg_id, int *msg_siz);
char *pop3_get_message (pop3_session_t *s, const unsigned int msg_id, const int max_size);
int pop3_del_message (pop3_session_t *s, const unsigned int msg_id);

#endif

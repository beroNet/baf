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

#ifndef __POP3_POP3_TIMER_H_
#define __POP3_POP3_TIMER_H_ 1

#include <pop3.h>

int __pop3_setup_sighandler (const pop3_session_t *s);
void __pop3_teardown_sighandler (const pop3_session_t *s);
void __pop3_start_timer (const pop3_session_t *s);
void __pop3_stop_timer (pop3_session_t *session);

#endif	/* __POP3_POP3_TIMER_H_ */


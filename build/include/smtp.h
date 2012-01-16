#ifndef _SMTP_H
#define _SMTP_H	1

typedef enum _smtp_ret_t {
	SMTP_HELLO		= 220,
	SMTP_GOODBYE		= 221,
	SMTP_AUTH_OK		= 235,
	SMTP_OK			= 250,
	SMTP_DATA		= 354,
	SMTP_AUTH_WAIT		= 334,
	SMTP_SYNTAX_CMD		= 500,
	SMTP_SYNTAX_ARG		= 501,
	SMTP_CMD_NOTIMPL	= 502,
	SMTP_CMD_BADSEQ		= 504,
	SMTP_PARM_NOTIMPL	= 504,
	SMTP_ERR_UNAVAILABLE	= 550,
	SMTP_ERR_USERNOTLOCAL	= 551,
	SMTP_ERR_ALLOC_EXCEED	= 552,
	SMTP_ERR_MAILBOX_NA	= 553,
	SMTP_ERR_TRANS_FAIL	= 554,
} smtp_ret_t;

typedef enum _smtp_auth_t {
	SMTP_AUTH_LOGIN		= 0x01,
	SMTP_AUTH_STARTTLS	= 0x02,
} smtp_auth_t;

typedef struct _smtp_mail_t {
	char	*from;
	char	*fname;
	char	*rcpt;
	char	*subj;
	char	*msg;
} smtp_mail_t;

#define SMTP_CMD_LEN		256
#define SMTP_USER_AGENT		"libsmtp"

int smtp_connect (const char *hostname, const unsigned short port, const char *username, const char *password);
int smtp_send_mail (const int sockfd, const smtp_mail_t mail, const char *user_agent);
void smtp_disconnect (const int sockfd);

#endif


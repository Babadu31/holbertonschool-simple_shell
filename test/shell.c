#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#if HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif

sig_atomic_t got_signal     = 0;    /* General signal flag (break capture) */

sig_atomic_t got_sighup     = 0;    /* SIGHUP flag  */
sig_atomic_t got_sigint     = 0;    /* SIGINT flag  */
sig_atomic_t got_sigterm    = 0;    /* SIGTERM flag */
sig_atomic_t got_sigusr1    = 0;    /* SIGUSR1 flag */
sig_atomic_t got_sigusr2    = 0;    /* SIGUSR2 flag */
sig_atomic_t got_sigchld    = 0;    /* SIGCHLD flag */

sigset_t    *csmask;

/* SIGHUP Handler
 */
void
sig_handler(int sig)
{
  int o_errno;
  got_signal = sig;

  switch(sig) {
  case SIGHUP:
    got_sighup = 1;
    return;
  case SIGINT:
    got_sigint = 1;
    return;
  case SIGTERM:
    got_sigterm = 1;
    return;
  case SIGUSR1:
    got_sigusr1 = 1;
    return;
  case SIGUSR2:
    got_sigusr2 = 1;
    return;
  case SIGCHLD:
    o_errno = errno; /* Save errno */
    got_sigchld = 1;
    waitpid(-1, NULL, WNOHANG);
    errno = o_errno; /* restore errno (in case reset by waitpid) */
    return;
  }
}

/* Setup signal handlers
 */
int set_sig_handlers(void)
{
int err = 0;
struct sigaction act;


got_signal     = 0;
got_sighup     = 0;
got_sigint     = 0;
got_sigterm    = 0;
got_sigusr1    = 0;
got_sigusr2    = 0;



act.sa_handler = sig_handler;
sigemptyset(&act.sa_mask);
act.sa_flags = SA_RESTART;

if(sigaction(SIGHUP, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGHUP handler: %s",
strerror(errno));
err++;
}

if(sigaction(SIGINT, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGINT handler: %s",
strerror(errno));
err++;
}

if(sigaction(SIGTERM, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGTERM handler: %s",
strerror(errno));
err++;
}

if(sigaction(SIGUSR1, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGUSR1 handler: %s",
strerror(errno));
err++;
}

if(sigaction(SIGUSR2, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGUSR2 handler: %s",
strerror(errno));
err++;
}

if(sigaction(SIGCHLD, &act, NULL) < 0)
{
log_msg(LOG_ERR, "* Error setting SIGCHLD handler: %s",
strerror(errno));
err++;
}

return(err);
}

int sig_do_stop(void)
{
  /* Any signal except USR1, USR2, and SIGCHLD mean break the loop.
   */
if(got_signal != 0)
{
if(got_sigint || got_sigterm || got_sighup)
{
return 1;
}
else if(got_sigusr1 || got_sigusr2)
{


got_sigusr1 = got_sigusr2 = 0;
got_signal = 0;
}
else
got_signal = 0;
}
return 0;
}

/**
 * main - dddd
 * @argv: dsdd
 * @argc: dsqdd
 * @env: sdsd
 * Return: ffd
 */
int main(int argc, char **argv, char **env)
{
size_t len = 0;
char *buf = 0;
char *token = 0;
int status = 0;
pid_t child = 0;


while (getline(&buf, &len, stdin) != -1)
{
token = strtok(buf, "\n");

child = fork();

if (child == 0)
{
if (execve(token, argv, env) == -1)
perror("./simpleshell");
free(buf);
return (0);
}
else
wait(&status);
buf = NULL;
}
return (0);
}

/*
** sig.c for sig in /home/theogalh/git/PSU_2016_ftrace/src
** 
** Made by theogalh
** Login   <thomas.bouillon@epitech.eu>
** 
** Started on  Sun May  7 17:12:44 2017 theogalh
** Last update Jan May 7 22:24:56 2017 Kaczor Alexandre
*/

#include <signal.h>
#include <stdio.h>

static	char	*sigtab[] =
  {
    "",
    "SIGHUP",
    "SIGINT",
    "SIGQUIT",
    "SIGILL",
    "SIGTRAP",
    "SIGIOT",
    "SIGBUS",
    "SIGFPE",
    "SIGKILL",
    "SIGUSR1",
    "SIGSEGV",
    "SIGUSR2",
    "SIGPIPE",
    "SIGALRM",
    "SIGTERM",
    "SIGSTKFLT",
    "SIGCHLD",
    "SIGCONT",
    "SIGSTOP",
    "SIGTSTP",
    "SIGTTIN",
    "SIGTTOU",
    "SIGURG",
    "SIGXCPU",
    "SIGXFSZ",
    "SIGVTALRM",
    "SIGPROF",
    "SIGWINCH",
    "SIGIO",
    "SIGPWR"
  };

void	print_sig(siginfo_t signal)
{
  if (signal.si_signo >= 1 && signal.si_signo <= 30 && signal.si_signo != 5)
    fprintf(stderr, "Received signal %s\n", sigtab[signal.si_signo]);
}

/*
** xptrace.c for xptrace in /home/amity/Rendu/c/unix/PSU_2016_strace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Tue Apr 11 15:46:43 2017 Alexandre
** Last update Jan May 7 22:25:21 2017 Kaczor Alexandre
*/

#include "ftrace.h"

int		kill_process(t_trace *data)
{
  waitpid(data->child, &data->status, 0);
  if (WIFEXITED(data->status)
      || WIFSIGNALED(data->status)
      || !(WIFSTOPPED(data->status)))
    return (1);
  return (0);
}

long	xptrace(enum __ptrace_request request, pid_t pid, void *addr,
		void *data)
{
  long	value;

  if ((value = ptrace(request, pid, addr, data)) == -1)
    {
      perror("ptrace");
      exit(1);
    }
  return (value);
}

/*
** misc.c for misc in /home/amity/Rendu/c/unix/PSU_2016_strace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Thu Apr 13 12:09:52 2017 Alexandre
** Last update Jan May 7 22:24:54 2017 Kaczor Alexandre
*/

#include "sysparam.h"

/*
**  050f syscall
**  340f sysenter
**  80cd int 0x80
*/

int		get_argv(char **env)
{
  int		i;

  i = 0;
  while (env[i])
    i++;
  return (i);
}

void	kill_strace(t_trace *data)
{
  ptrace(PTRACE_KILL, data->child, NULL, NULL);
  free(data->process);
  exit(1);
}

int	is_syscall(unsigned short opcode)
{
  if (!(opcode ^ 0x050f) || !(opcode ^ 0x340f) || !(opcode ^ 0x80cd))
    return (1);
  return (0);
}

int	get_parameter(char *data)
{
  t_inc	x;

  x.i = 0;
  x.j = 0;
  x.size = 0;
  while (g_data[x.i].name && (strcmp(g_data[x.i].name, data) != 0))
    x.i++;
  while (g_data[x.i].argv[x.j] != NULL)
    x.j++;
  return (x.j);
}

int	*init_reg(struct user_regs_struct *data)
{
  int	*reg;

  if ((reg = malloc(sizeof(unsigned long int) * MAX_PARAM)) == NULL)
    return (NULL);
  reg[0] = data->rdi;
  reg[1] = data->rsi;
  reg[2] = data->rdx;
  reg[3] = data->r10;
  reg[4] = data->r8;
  reg[5] = data->r9;
  return (reg);
}

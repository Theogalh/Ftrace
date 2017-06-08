/*
** print_flag.c for flag in /home/amity/Rendu/c/unix/PSU_2016_strace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Fri Apr 14 19:48:08 2017 Alexandre
** Last update Jan May 7 22:24:55 2017 Kaczor Alexandre
*/

#include "ftrace.h"

void		print_execv(t_trace *data)
{
  if (data->process)
  {
    fprintf(stderr, "Syscall execve(\"%s\", [\"%s\"], [/* %d vars */]) = 0\n",
    data->process,
    (strrchr(data->process, '/') == NULL ? data->process :
    strrchr(data->process, '/') + 1), data->nb_argv);
  }
}

void	print_hexa(int *reg, t_inc x, t_trace *data, char *str)
{
  while (++x.i < x.size)
    {
      if (x.i + 1 != x.size)
       	fprintf(stderr, "0x%x, ", (unsigned int)reg[x.i]);
      else
	fprintf(stderr, "0x%x", (unsigned int)reg[x.i]);
    }
  fprintf(stderr, ") ");
  print_ret(data);
  if ((strcmp("exit_group", str)) == 0)
    {
      fprintf(stderr, "Leaving function %s\n", "main");
      fprintf(stderr, "+++ exited with 0x%x +++\n",
	      (unsigned int)data->infos.regs.rdi);
      kill_strace(data);
    }
}

void	print_ret(t_trace *data)
{
  ptrace(PTRACE_SINGLESTEP, data->child, NULL, NULL);
  waitpid(data->child, &data->status, 0);
  if ((ptrace(PTRACE_GETREGS, data->child, NULL, &data->infos)) == -1)
    {
      fprintf(stderr, " = ?\n");
      return ;
    }
  else
    fprintf(stderr, " = 0x%x\n", (unsigned int)data->infos.regs.rax);
}

void	dumpregs(t_trace *data, char *str)
{
  t_inc	x;
  int	*my_reg;

  x.i = -1;
  x.size = get_parameter(str);
  my_reg = init_reg(&data->infos.regs);
  fprintf(stderr, "Syscall %s(", str);
  print_hexa(my_reg, x, data, str);
}

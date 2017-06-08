/*
** ftrace.c for ftrace in /home/amity/epitech/tek2/PSU_2016_ftrace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Tue Apr 25 13:55:12 2017 Alexandre
** Last update Sun May  7 21:38:31 2017 Kaczor Alexandre
*/

#include "nm.h"
#include "syscalls.h"

int		g_size = 0;
int		g_max = 0;

void		check_my_list(t_trace *data, t_list *func, t_list *this,
			      char **name)
{
  t_list	*tmp;

  tmp = this;
  while (tmp->next)
    {
      if ((int)data->infos.regs.rip == tmp->addr)
	{
	  if (check_func(tmp->name))
	    {
	      *name = strdup(tmp->name);
	      fprintf(stderr,"Entering function %s at %lx\n",
		      tmp->name, (long unsigned int)tmp->addr);
	      list_add_elem_at_back(func, tmp->addr, 'X', tmp->name);
	      g_max++;
	      return ;
	    }
	}
      tmp = tmp->next;
    }
}

void		print_func(t_trace *data, t_list *func, char *name)
{
  t_list	*tmp;

  if (IS_RET(data->opcode))
    {
      if (name != NULL)
	{
	  if (((data->opcode & 0xFF) == 0xC3
	       || (data->opcode & 0xFF) == 0xC2
	       || (data->opcode & 0xFF) == 0xCB
	       || (data->opcode & 0xFF) == 0xCA)
	      && g_size < g_max - 1)
	    {
	      tmp = func;
	      if (tmp == NULL)
	      	return ;
	      while (tmp->next)
		tmp = tmp->next;
	      fprintf(stderr, "Leaving function %s\n", tmp->name);
	      list_del_elem_at_back(tmp->next);
	      g_size++;
	    }
	}
    }
}

int		process_trace(t_trace *data, t_list *this)
{
  t_list	func;
  char		*name;
  siginfo_t	signal;

  print_execv(data);
  while (!kill_process(data))
    {
      xptrace(PTRACE_GETREGS, data->child, NULL, &data->infos);
      data->opcode = xptrace(PTRACE_PEEKTEXT, data->child,
			     (void *)data->infos.regs.rip, NULL);
      xptrace(PTRACE_GETSIGINFO, data->child, NULL, &signal);
      if (is_syscall(data->opcode))
	dumpregs(data, syscall_names[data->infos.regs.rax]);
      else if (this)
	check_my_list(data, &func, this, &name);
      print_sig(signal);
      print_func(data, &func, name);
      xptrace(PTRACE_SINGLESTEP, data->child, NULL, NULL);
    }
  return (0);
}

void		trace_exec(t_trace *data, t_list *this)
{
  data->offset = find_offset(data->path, data->process);
  if (data->offset < 0)
    {
      if (access(data->process, F_OK | X_OK) == 0 &&
	  (strncmp("./", data->process, 2) == 0 ||
	   (strncmp("/", data->process, 1) == 0)))
	data->process = strdup(data->process);
      else
	{
	  fprintf(stderr, "ftrace: '%s': no such file or directory\n"
		  , data->process);
	  return ;
	}
    }
  else
    data->process = strdup(data->path[data->offset]);
  data->child = fork();
  if (data->child == 0)
    {
      xptrace(PTRACE_TRACEME, 0, NULL, NULL);
      execvp(data->process, data->cmd);
    }
  else
    process_trace(data, this);
  my_free_wordtab(data->path);
}

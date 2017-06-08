/*
** strace.h for strace in /home/amity/Rendu/c/unix/strace
**
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
**
** Started on  Mon Apr  3 14:11:46 2017 Alexandre
** Last update Sun May  7 21:39:00 2017 Kaczor Alexandre
*/

#ifndef STRACE_H_

# define STRACE_H_
# define MAX_PARAM 7
# define IS_RET(x) ((x & 0x3800) == 0x1000 ? 1 : 0)

# include "nm.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/ptrace.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/reg.h>
# include <sys/user.h>
# include <signal.h>
# include <unistd.h>

typedef struct		s_strace
{
  struct user		infos;
  siginfo_t		sig;
  pid_t			child;
  short			opcode;
  char			**path;
  char			*process;
  char			**cmd;
  int			nb_argv;
  int			offset;
  int			status;
}			t_trace;

typedef struct		s_tab
{
  char			**path;
  int			i;
  int			l;
  int			j;
  int			k;
}			t_tab;

typedef struct		s_sys
{
  char			*name;
  char			*ret;
  char			*argv[MAX_PARAM];
}			t_sys;

typedef struct		s_inc
{
  int			i;
  int			j;
  int			k;
  int			count;
  int			size;
  int			length;
}			t_inc;

/* main.c */

char			*strcat_path(char *, char *);
char			**get_path(char **);
char			**my_str_to_wordtab(char *, char);
int			process_trace(t_trace *, t_list *);
int			find_offset(char **, char *);
int			get_parameter(char *);
int			is_syscall(unsigned short);
long			xptrace(enum __ptrace_request, pid_t, void *, void *);
void			trace_exec(t_trace *, t_list *);
void			trace_pid(t_trace *);
void			my_show_wordtab(char **);
void			my_free_wordtab(char **);
void			check_arg(int, char **, t_trace *);
void			kill_strace(t_trace *);
void			print_hexa(int *, t_inc, t_trace *, char *);
void			print_trace(int *, t_inc, t_trace *, char *);
void			print_ret(t_trace *);
void			dumpregs(t_trace *, char *);
void			print_execv(t_trace *);
void			print_sig(siginfo_t);
int			kill_process(t_trace *);
t_list			*get_sym(t_list *, char *, t_nm *, int);
int			get_argv(char **);
int			*init_reg(struct user_regs_struct *);

#endif /* !STRACE_H_ */

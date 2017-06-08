/*
** main.c for ftrace in /home/amity/epitech/tek2/PSU_2016_ftrace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Mon Apr 24 13:31:36 2017 Alexandre
** Last update Jan May 7 22:25:20 2017 Kaczor Alexandre
*/

#include "ftrace.h"

static t_list	*init_tlist(t_trace *);

static char	**get_args(int argc, char **argv)
{
  int		i;
  int		y;
  char		**cmd;

  i = 0;
  y = 1;
  if ((cmd = malloc(sizeof(char *) * argc)) == NULL)
    return (NULL);
  while (y != argc)
    {
      cmd[i] = strdup(argv[y]);
      i = i + 1;
      y = y + 1;
    }
  return (cmd);
}

static int	init_trace(t_trace *data, int argc, char **argv, char **env)
{
  data->cmd = get_args(argc, argv);
  data->process = strdup(argv[1]);
  data->nb_argv = get_argv(env);
  data->path = get_path(env);
  return (0);
}

static t_list	*init_tlist(t_trace *data)
{
  t_list	*list;
  t_nm		this;

  list = NULL;
  this = init_sym(data->process);
  if (this.fd < 0 || this.data == MAP_FAILED)
    return (NULL);
  if (check_format(&this, data->process))
    {
      this.shdr = (Elf64_Shdr *)((char *)this.data + this.elf->e_shoff);
      this.sym = (Elf64_Sym *)((char *)this.data + this.shdr->sh_offset);
      this.shtab = this.data + this.shdr[this.elf->e_shstrndx].sh_offset;
      list = get_sym(list, data->process, &this, this.elf->e_shnum);
    }
  close(this.fd);
  return (list);
}

int		main(int argc, char **argv, char **env)
{
  t_trace	f;
  t_list	*list;

  if (argc < 2)
    fprintf(stderr, "Usage ./ftrace <command>\n");
  else
    {
      (void)list;
      init_trace(&f, argc, argv, env);
      list = init_tlist(&f);
      trace_exec(&f, list);
    }
  return (0);
}

/*
** strace.c for sys in /home/amity/Rendu/c/unix/PSU_2016_strace
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Thu Apr 13 12:09:32 2017 Alexandre
** Last update Jan May 7 22:25:13 2017 Kaczor Alexandre
*/

#include "nm.h"

void		get_strtab(t_nm *this, int shnum)
{
  this->i = 1;
  while (this->i < shnum)
    {
      if (this->shdr[this->i].sh_type == SHT_STRTAB)
	this->str = (char *)((char *)this->data +
			     this->shdr[this->i].sh_offset);
      this->i++;
    }
}

t_list		*get_my_symbol(t_nm *this, t_list *list)
{
  t_size	s;

  s.i = 0;
  s.j = 1;
  s.size = (SH_HEADER / sizeof(Elf64_Sym));
  while (s.j < s.size)
    {
      if (check_type_sym(this, s.j))
	{
	  if (strncmp("_", &this->str[SYM_NAME], 1) != 0 &&
	      (PRINT_T == 'U' || PRINT_T == 'T'))
	    {
	      if (s.i == 0)
	      	list = init_list(SYM_VAL, PRINT_T, &this->str[SYM_NAME]);
	      list_add_elem_at_back(list, SYM_VAL, PRINT_T,
				    &this->str[SYM_NAME]);
	      s.i++;
	    }
	}
      s.j++;
    }
  return (list);
}

t_list		*get_sym(t_list *list, char *file, t_nm *this, int shnum)
{
  int		have_sym;

  get_strtab(this, shnum);
  this->i = 1;
  have_sym = 0;
  while (this->i < shnum)
    {
      if (this->shdr[this->i].sh_type == SHT_SYMTAB)
	{
	  have_sym = 1;
	  this->sym = (Elf64_Sym *)((char *)this->data
				    + this->shdr[this->i].sh_offset);
	  list = get_my_symbol(this, list);
	}
      this->i++;
    }
  if (!have_sym)
    {
      fprintf(stderr, "ftrace: %s: no symbols\n", file);
      exit(1);
    }
  return (list);
}

t_nm	init_sym(char *cmd)
{
  t_nm	this;

  if ((this.fd = open(cmd, O_RDONLY)) == -1)
    {
      show_error(cmd, 1);
      return (this);
    }
  this.data = mmap(NULL, fsize(this.fd), PROT_READ, MAP_SHARED, this.fd, 0);
  if (this.data == MAP_FAILED)
    {
      show_error(cmd, 0);
      return (this);
    }
  this.elf = (Elf64_Ehdr *)this.data;
  return (this);
}

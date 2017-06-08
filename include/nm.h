/*
** my.h for header in /home/alexandre.kaczor/rendu/tek2/unix/PSU_2016_nmobjdump/src/objdump
**
** Made by Kaczor Alexandre
** Login   <alexandre.kaczor@epitech.net>
**
** Started on  Tue Feb 14 14:35:01 2017 Kaczor Alexandre
** Last update Sun May  7 21:40:17 2017 Kaczor Alexandre
*/

#ifndef MY_H_
# define MY_H_

# include <elf.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <ctype.h>
# include <stdbool.h>
# include <string.h>

# define SH_OFFSET	this->shdr[this->i].sh_offset
# define SH_HEADER	this->shdr[this->i].sh_size
# define SH_NAME	&this->shtab[this->shdr[sym.st_shndx].sh_name]
# define SH_ADDR	this->shdr[this->i].sh_addr
# define SYM_VAL	(unsigned int)this->sym[s.j].st_value
# define SYM_NAME	this->sym[s.j].st_name
# define PRINT_T	print_type(this, this->sym[s.j] , this->shdr)

typedef struct	s_nm
{
  void		*data;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
  Elf64_Sym	*sym;
  bool		isRel;
  char		*str;
  char		*shtab;
  int		fd;
  int		i;
  int		count;
}		t_nm;

typedef struct  s_size
{
  size_t        i;
  size_t        j;
  size_t        k;
  size_t        l;
  size_t        size;
}               t_size;

typedef struct	s_list
{
  int		addr;
  char		c;
  char*		name;
  struct s_list	*next;
}		t_list;

void		parse_av(int, char **);
void		print_data(char *, t_nm *, int);
bool		check_format(t_nm *, char *);
char		print_type(t_nm *, Elf64_Sym, Elf64_Shdr*);
bool		check_type_sym(t_nm *, int);
void		show_error(char *, int);
off_t		fsize(int);
t_list		*init_list(int, char, char *);
t_list		*sort_list(t_list *);
void		list_del_elem_at_back(t_list *);
void		remove_doublon(t_list *);
void		list_add_elem_at_back(t_list *, int, char, char *);
void		show_nm(t_list *, t_nm *);
void		free_list(t_list *);
int		list_size(t_list *);
int		check_func(char *);
void		swap_name(t_list *);
char		*my_epurstr(char *);
bool		charcmp(char *s1, char *s2);
char		*char_to_lower(char *s1);
void		init_var(t_size *l, int *val1, int *val2);
t_nm		init_sym(char *);

#endif /* !NM_H_ */

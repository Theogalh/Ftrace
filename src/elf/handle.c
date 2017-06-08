/*
** handle.c for main in /home/amity/epitech/tek2/PSU_2016_ftrace/src/nm
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Mon Apr 24 19:46:53 2017 Alexandre
** Last update Jan May 7 22:25:16 2017 Kaczor Alexandre
*/

#include "nm.h"

void	show_error(char *str, int error)
{
  if (!error)
    fprintf(stderr, "Warning: '%s' is not an ordinary file\n", str);
  return ;
}

off_t	fsize(int fd)
{
  off_t	s;

  if ((s = lseek(fd, 0, SEEK_END)) == -1)
    return (0);
  return (s);
}

bool	check_format(t_nm *this, char *file)
{
  if (this->elf->e_ident[EI_MAG0] != ELFMAG0 ||
      this->elf->e_ident[EI_MAG1] != ELFMAG1 ||
      this->elf->e_ident[EI_MAG2] != ELFMAG2 ||
      this->elf->e_ident[EI_MAG3] != ELFMAG3)
    {
      fprintf(stderr, "ftrace: %s: File format not recognized\n", file);
      return (false);
    }
  if (this->elf->e_type == ET_REL)
    this->isRel = true;
  else
    this->isRel = false;
  return (true);
}

bool	check_type_sym(t_nm *this, int pos)
{
  if (this->sym[pos].st_info == STT_SECTION ||
      this->sym[pos].st_info == STT_FILE ||
      this->sym[pos].st_info == STT_NOTYPE)
    return (false);
  return (true);
}

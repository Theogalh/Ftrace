/*
** other.c for ok in /home/alexandre.kaczor/rendu/tek2/unix/PSU_2016_ftrace
** 
** Made by Kaczor Alexandre
** Login   <alexandre.kaczor@epitech.net>
** 
** Started on  Sun May  7 21:37:51 2017 Kaczor Alexandre
** Last update Sun May  7 21:40:01 2017 Kaczor Alexandre
*/

#include "nm.h"

int		check_func(char *name)
{
  int		i;

  i = 0;
  while (name[i])
    {
      if (name[i] == '@')
	return (-1);
      i++;
    }
  return (1);
}

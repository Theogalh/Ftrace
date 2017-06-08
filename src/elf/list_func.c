/*
** list_func.c for list in /home/alexandre.kaczor/rendu/tek2/unix/PSU_2016_nmobjdump/src/nm
** 
** Made by Kaczor Alexandre
** Login   <alexandre.kaczor@epitech.net>
** 
** Started on  Sun Feb 19 00:50:20 2017 Kaczor Alexandre
** Last update Jan May 7 22:25:15 2017 Kaczor Alexandre
*/

#include "nm.h"

void		remove_doublon(t_list *list)
{
  t_list*	tmp;
  t_list*	next;

  tmp = list;
  if (tmp == NULL)
    return;
  while (tmp->next != NULL)
    {
      if (tmp->name == tmp->next->name)
	{
	  next = tmp->next->next;
	  free(tmp->next);
	  tmp->next = next;
	}
      else
	tmp = tmp->next;
    }
}

void		free_list(t_list *list)
{
  t_list	*elem;

  if (list == NULL)
    return ;
  elem = list;
  while (elem->next != NULL)
    {
      if (elem->name)
	free(elem->name);
      elem = elem->next;
    }
  if (elem->name)
    free(elem->name);
}

int		list_size(t_list *list)
{
  int		i;
  t_list	*elem;

  if (list == NULL)
    return (0);
  elem = list;
  while (elem->next != NULL)
    {
      elem = elem->next;
      i++;
    }
  return (i);
}

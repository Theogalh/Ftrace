/*
** list.c for list in /home/alexandre.kaczor/rendu/tek2/unix/PSU_2016_nmobjdump/src/nm
** 
** Made by Kaczor Alexandre
** Login   <alexandre.kaczor@epitech.net>
** 
** Started on  Sat Feb 18 12:54:46 2017 Kaczor Alexandre
** Last update Sun May  7 21:36:19 2017 Kaczor Alexandre
*/

#include "nm.h"

t_list		*get_new_node(int addr, char c, char *name)
{
  t_list	*new;

  if ((new = malloc(sizeof(t_list))) == NULL)
    return (NULL);
  new->addr = addr;
  new->c = c;
  if ((new->name = malloc(strlen(name))) == NULL)
    return NULL;
  new->name = name;
  new->next = NULL;
  return new;
}

t_list		*init_list(int addr, char c, char *name)
{
  t_list	*new_node;

  new_node = get_new_node(addr, c, name);
  if (new_node == NULL)
    return NULL;
  return new_node;
}

void		list_add_elem_at_back(t_list *my_list, int addr, char c,
				      char *name)
{
  t_list	*new_node;
  t_list	*old_node;

  new_node = get_new_node(addr, c, name);
  old_node = my_list;
  if (my_list == NULL)
    old_node = init_list(addr, c, name);
  if (new_node == NULL)
    return ;
  while (old_node->next != NULL)
    old_node = old_node->next;
  old_node->next = new_node;
  return ;
}

void		list_del_elem_at_back(t_list *data)
{
  t_list	*curr;

  if (data == NULL)
    return ;
  curr = data;
  while (curr->next != NULL)
    {
      data = curr;
      curr = curr->next;
    }
  free(data->next);
  data->next = NULL;
}

/*
** my_str_to_wordtab.c for wordtab in /home/amity/Rendu/c/unix/strace
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Mon Apr  3 13:24:41 2017 Alexandre
** Last update Jan May 7 22:25:18 2017 Kaczor Alexandre
*/

#include "ftrace.h"

void	my_show_wordtab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i])
    printf("%s\n", tab[i]);
}

void	my_free_wordtab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  if (tab[i])
    free(tab[i]);
  free(tab);
}

int	count_word(char *str, char delim)
{
  int	i;
  int	word;

  i = 0;
  word = 0;
  while (str[i])
    {
      if (str[i] == delim)
	word++;
      else if (str[i + 1] == '\0')
	word++;
      i++;
    }
  return (word);
}

int	c_char(char *str, char delim)
{
  int	i;
  int	charac;

  i = 0;
  charac = 0;
  if (str[i] == delim)
    i++;
  while (str[i])
    {
      if (str[i] == delim || str[i + 1] == '\0')
	return (charac);
      else
	charac++;
      i++;
    }
  return (0);
}

char	**my_str_to_wordtab(char *str, char d)
{
  t_tab	x;

  x.i = 0;
  x.k = 0;
  x.l = 0;
  x.j = count_word(str, d);
  if ((x.path = malloc(sizeof(char *) * (x.j + 1))) == NULL)
    return (NULL);
  while (str[x.i] != '\0')
    {
      if (c_char(str + x.i, d) > 0)
	{
	  if ((x.path[x.l] = malloc((c_char(str + x.i, d) + 2))) == NULL)
	    return (NULL);
	  while (str[x.i] != d && str[x.i])
	    x.path[x.l][x.k++] = str[x.i++];
	  x.path[x.l][x.k] = '\0';
	  x.l++;
	  x.k = 0;
	}
      x.i++;
    }
  x.path[x.l] = NULL;
  free(str);
  return (x.path);
}

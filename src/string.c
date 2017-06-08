/*
** string.c for string in /home/amity/Rendu/c/unix/PSU_2016_strace/src
** 
** Made by Alexandre
** Login   <alexandre.kaczor@epitech.eu>
** 
** Started on  Mon Apr 10 12:45:08 2017 Alexandre
** Last update Jan May 7 22:24:57 2017 Kaczor Alexandre
*/

#include "ftrace.h"

int	check_binary(char *str)
{
  if (strlen(str) > 2)
    if (str[0] == '.' && str[1] == '/')
      return (1);
  return (0);
}

int	find_offset(char **data, char *bin)
{
  int	offset;
  int	i;

  i = 0;
  offset = 0;
  if (check_binary(bin))
    return (-1);
  while (data[i])
    {
      if ((data[i] = realloc(data[i], strlen(data[i]) + strlen(bin) + 2))
	  == NULL)
	return (-1);
      bin = (strrchr(bin, '/') == NULL ? bin : strrchr(bin, '/') + 1);
      data[i] = strcat_path(data[i], bin);
      if (access(data[i], F_OK | X_OK) == 0)
	offset = i;
      i++;
    }
  return (offset > 0 ? offset : -1);
}

char    *path_cpy(char *dest, char *src)
{
  int   i;
  int   a;

  i = 0;
  a = 0;
  if (dest == NULL || src == NULL)
    return (NULL);
  while (src[i] != '=')
    i++;
  i++;
  while (src[i] != '\0')
    {
      dest[a] = src[i];
      i = i + 1;
      a = a + 1;
    }
  dest[a] = '\0';
  return (dest);
}

char    *strcat_path(char *dest, char *src)
{
  int   a;
  int   b;

  a = 0;
  b = 0;
  if (dest == NULL || src == NULL)
    return (NULL);
  while (dest[b] != '\0')
    b = b + 1;
  if (dest[b - 1] != '/')
    dest[b++] = '/';
  while (src[a] != '\0')
    {
      dest[b] = src[a];
      b = b + 1;
      a = a + 1;
    }
  dest[b] = '\0';
  return (dest);
}

char	**get_path(char **env)
{
  char	**path;
  char	*str;
  int	i;

  i = 0;
  while (env[i])
    {
      if (strncmp("PATH", env[i], 4) == 0)
	{
	  if ((str = malloc(sizeof(char) * strlen(env[i]))) == NULL)
	    return (NULL);
	  str = path_cpy(str, env[i]);
	}
      i++;
    }
  path = my_str_to_wordtab(str, ':');
  return (path);
}

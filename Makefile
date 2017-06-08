##
## Makefile for ake in /home/amity/Rendu/c/unix/strace
## 
## Made by Alexandre
## Login   <alexandre.kaczor@epitech.eu>
## 
## Started on  Mon Apr  3 13:24:25 2017 Alexandre
## Last update Sun May  7 21:39:35 2017 Kaczor Alexandre
##

NAME		= 	ftrace

SRC		=	src/main.c \
			src/ftrace.c \
			src/string.c \
			src/print_flag.c \
			src/misc.c \
			src/xptrace.c \
			src/sig.c \
			src/other.c \
			src/elf/handle.c \
			src/elf/nm_sym.c \
			src/elf/list.c \
			src/elf/list_func.c \
			src/elf/type.c \
			src/tools/my_str_to_wordtab.c \

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-I./include -W -Wall -Wextra

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			cc $(OBJ) -o $(NAME) $(CFLAGS)
			@echo -e "\033[1;32mCompilation Ftrace 100%\033[0;m"

clean		:
			rm -f $(OBJ)
			@echo -e "\033[1;33mClean 100%\033[0;m"

fclean		:	clean
			rm -f $(NAME)
			@echo -e "\033[1;33mFclean 100%\033[0;m"

re		:	fclean all

.PHONY		:	all clean fclean re

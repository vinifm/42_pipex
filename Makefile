# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 15:59:03 by viferrei          #+#    #+#              #
#    Updated: 2022/03/21 16:16:55 by viferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libft
LIBFT 		= $(LIBFT_DIR)/libft.a
LEAKS_FILE	= valgrind-log.txt
LFLAGS		= --leak-check=full \
				--log-file=$(LEAKS_FILE) \
				--show-leak-kinds=all \
				--track-origins=yes \
				./pipex

SRCDIR	= ./srcs/
SRC		= $(SRCDIR)test.c
OBJ		= $(notdir $(SRC:.c=.o)) # removes "./srcs/" from .o files.

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -I ./include $(SRC)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

leaks: re
	$(RM) $(LEAKS_FILE)
	valgrind $(LFLAGS)

.PHONY: all clean fclean re

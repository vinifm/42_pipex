# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 15:59:03 by viferrei          #+#    #+#              #
#    Updated: 2022/03/29 17:00:08 by viferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libft
LIBFT 		= $(LIBFT_DIR)/libft.a

SRCDIR	= ./srcs/
OBJDIR	= ./objs/

SRC		= pipex.c
OBJ		= = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -I ./include $(SRC)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

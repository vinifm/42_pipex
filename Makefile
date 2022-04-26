# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 15:59:03 by viferrei          #+#    #+#              #
#    Updated: 2022/04/26 22:09:46 by viferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libft
LIBFT 		= $(LIBFT_DIR)/libft.a
LFLAGS		= --leak-check=full \
				--show-leak-kinds=all \
				--trace-children=yes \
				--track-origins=yes \
				./pipex infile "gdasds" "tdasda" outfile

SRCDIR	= ./srcs/
OBJDIR	= ./objs/

SRC			= pipex.c \
				utils.c \
				split.c
SRC_BONUS	= pipex_bonus.c \
				utils_bonus.c \
				split_bonus.c
OBJ			= $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))
OBJ_BONUS	= $(addprefix $(OBJDIR), $(notdir $(SRC_BONUS:.c=.o)))

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I ./include -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LIBFT)

rebonus: fclean bonus

leaks:
	valgrind $(LFLAGS)

.PHONY: all clean fclean re bonus rebonus

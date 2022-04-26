# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 15:59:03 by viferrei          #+#    #+#              #
#    Updated: 2022/04/25 21:20:49 by viferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libft
LIBFT 		= $(LIBFT_DIR)/libft.a

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

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(NAME_BONUS)

cleanb:
	$(RM) $(OBJ_BONUS)
	make clean -C $(LIBFT_DIR)

fcleanb: cleanb
	$(RM) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

rebonus: fcleanb
	make bonus

.PHONY: all clean fclean re bonus cleanb fcleanb rebonus

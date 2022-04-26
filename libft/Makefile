CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf
LIB		= ar -rcs

NAME	= libft.a

INCLUDE	= libft.h
SRC		= ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_substr.c
OBJ_DIR	= ./objs
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: 		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
			$(LIB) $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:	%.c	$(INCLUDE)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ_DIR)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re

run:		$(NAME)
			$(RM) a.out
			$(CC) $(CFLAGS)	main.c libft.a && ./a.out

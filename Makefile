CC = cc

NAME = minishell

LIBFT = libft/libft.a

SRC = main.c ft_utils.c ft_prompt.c ft_clean_input.c

OBJ = $(SRC:.c=.o) $(LIBFT)

HEADER = minishell.h

CFLAGS = -Wall -Wextra -Werror -g

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c  $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) -lreadline $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
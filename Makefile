NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
SRC 		= 			./src/main.c \
						./src/ft_utils.c\
						./src/ft_prompt.c\
						./src/ft_clean_input.c\
						./src/ft_lexer.c\
						./src/ft_free.c\
						./src/ft_matrix_support.c \
						./src/ft_checks.c\
						./src/ft_little_executer.c\
						./src/builtin/ft_unset.c\
						./src/builtin/ft_export.c \
						./src/builtin/ft_builtin.c\

LIB			= ./libft/libft.a

OBJ = $(SRC:.c=.o)

HEADER = minishell.h


%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c  $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	@make -sC ./libft 
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME) $(LIB)

clean:
	@make -sC ./libft clean 
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(OBJ)
	@make -sC ./libft fclean
	@rm -f $(NAME)

cmp:
	@make -sC ./libft

re: fclean all


.PHONY: all clean fclean re bonus
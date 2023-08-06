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

ASCII_ART_FILE := name_shell.txt

ascii_art: $(ASCII_ART_FILE)
		@echo "$$(cat $(ASCII_ART_FILE))"

OBJ = $(SRC:.c=.o)

HEADER = minishell.h


%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c  $< -o $@

all : $(NAME)  $(ascii_art)

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
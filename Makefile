NAME			= minishell

CC				= cc

CFLAGS			= -Wall -Wextra -Werror
SRC				= ft_unset.c \
				ft_export.c \
				ft_builtin.c \
				ft_chdir.c \
				ft_checks.c \
				ft_colors.c \
				ft_counts.c \
				ft_execute.c \
				ft_free.c \
				ft_lexer_write.c \
				ft_lexer.c \
				ft_little_executer.c \
				ft_matrix_support.c \
				ft_pipe.c \
				ft_prompt.c \
				ft_redirects.c \
				ft_tokenize.c \
				ft_tokens_args.c \
				ft_utils.c \
				main.c

SRCS			= ${addprefix ${PRE}, ${SRC}}

DIR_OBJS		= objs/

PRE				= src/
OBJS			= ${SRCS:.c=.o}
PRE_OBJS		= ${addprefix ${DIR_OBJS}, ${OBJ}}

LIB				= ./libft/libft.a

ASCII_ART_FILE	:= name_shell.txt

OBJ				= $(SRC:.c=.o)

HEADER			= minishell.h

all:			$(NAME)

%.o:%.c			$(HEADER)
				@$(CC) $(CFLAGS) -c  $< -o $@

$(NAME):		
				@if [ ! -f ${NAME} ]; then \
					make -s ${OBJS} dup_obj ${PRE_OBJS}; \
					make -sC ./libft; \
					$(CC) $(CFLAGS) $(PRE_OBJS) -lreadline -o $(NAME) $(LIB); \
					make -s ascii_art; \
				fi

dup_obj:
				@mkdir -p ${DIR_OBJS}
				@mv ${OBJS} ${DIR_OBJS}

loading:
				@echo -ne 'LOADING\033[0;5m...\r'
				@sleep 1
				@echo -ne '\033[0;32m⦗❚❚❚❚❚❚                   ⦘(25%)\r'
				@sleep 0.2
				@echo -ne '⦗❚❚❚❚❚❚❚❚❚❚❚❚❚            ⦘(50%)\r'
				@sleep 0.2
				@echo -ne '⦗❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚     ⦘(75%)\r'
				@sleep 0.2
				@echo -ne '⦗❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚❚⦘(100%)\033[0m\r'
				@sleep 0.2

ascii_art:		loading $(ASCII_ART_FILE)
				@echo "$$(cat $(ASCII_ART_FILE))"

clean:
				@make -sC ./libft clean
				@if [ -d ${DIR_OBJS} ]; then \
					rm -rf ${DIR_OBJS}; \
					echo 'REMOVED OBJS'; \
				fi

fclean:			clean
				@make -sC ./libft fclean
				@if [ -f ${NAME} ]; then \
					rm -f ${NAME}; \
					echo 'MINISHELL UNINSTALLED'; \
				fi

re:				fclean all

.PHONY			= all clean fclean re
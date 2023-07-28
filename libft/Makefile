# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschiavo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:46:15 by cschiavo          #+#    #+#              #
#    Updated: 2022/12/09 10:03:47 by cschiavo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

SRC :=	base_function/ft_atoi.c\
	base_function/ft_bzero.c\
	base_function/ft_calloc.c\
	base_function/ft_isalnum.c\
	base_function/ft_isalpha.c \
	base_function/ft_isascii.c\
	base_function/ft_isdigit.c\
	base_function/ft_isprint.c\
	base_function/ft_itoa.c\
	base_function/ft_memchr.c\
	base_function/ft_memcmp.c\
	base_function/ft_memcpy.c\
	base_function/ft_memmove.c\
	base_function/ft_memset.c\
	base_function/ft_putchar_fd.c\
	base_function/ft_putendl_fd.c\
	base_function/ft_putnbr_fd.c\
	base_function/ft_putstr_fd.c\
	base_function/ft_split.c\
	base_function/ft_strchr.c\
	base_function/ft_strdup.c\
	base_function/ft_strjoin.c\
	base_function/ft_strlcat.c\
	base_function/ft_strlcpy.c\
	base_function/ft_strlen.c\
	base_function/ft_strmapi.c\
	base_function/ft_strncmp.c\
	base_function/ft_strnstr.c\
	base_function/ft_strrchr.c\
	base_function/ft_substr.c\
	base_function/ft_tolower.c\
	base_function/ft_toupper.c\
	base_function/ft_striteri.c\
	base_function/ft_split.c\
	base_function/ft_strtrim.c

PTF :=	ft_printf/ft_printstring.c\
	ft_printf/ft_printfchar.c\
	ft_printf/ft_print_d.c\
	ft_printf/ft_print_x.c\
	ft_printf/ft_printf.c\
	ft_printf/ft_printfu.c\
	ft_printf/ft_printfp.c\

GNL :=	get_next_line/get_next_line_bonus.c\


BNS :=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ_S = $(SRC:.c=.o) $(GNL:.c=.o) $(PTF:.c=.o)

OBJ_B = $(BNS:.c=.o) $(GNL:.c=.o) $(PTF:.c=.o)

CFLAG = -Wall -Werror -Wextra

all: $(NAME) status

$(NAME): $(OBJ_S)
	ar -rcs $@ $^ 


%.o:%.c
	@$(CC) -c $(CFLAG) -I. $< -o $@
status:
	echo "\033[5;1;92mcompleted\033[0m"
clean: status
	/bin/rm -f base_function/*.o
	/bin/rm -f ft_printf/*.o
	/bin/rm -f get_next_line/*.o

fclean:	clean
	/bin/rm -f $(NAME)

re: fclean all


bonus: $(OBJ_B)
	ar -rcs $(NAME) $^

.PHONY: all clean fclean re bonus
.SILENT:

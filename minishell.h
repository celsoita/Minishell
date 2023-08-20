/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:54:09 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 13:35:04 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ================================INCLUDE======================================
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <term.h>
# include <sys/types.h>
# include <curses.h>
# include <sys/wait.h>
# include "libft/libft.h"

// ==============================STRUCT & ENUM==================================
typedef struct s_stds
{
	int	stdin;
	int	stdout;
}	t_stds;

typedef struct s_ops
{
	int	n_pipe;
	int	*pipe;
	int	n_redirect;
	int	*redirect;
}	t_ops;

typedef struct s_lexer
{
	char			**tokens;
	char			**global_tokens;
	char			**paths;
	int				flags;
	char			**env_copy;
	int				lenght;
	char			*cwd;
	bool			absolute_path;
	int				pipe_num;
	t_ops			op;
	t_stds			stds;
	bool			can_return;
	unsigned char	return_value;
	int				current_pipe;
	int				current_redirect;
	char			**args;
	bool			is_executing;
}	t_lexer;

typedef struct s_prompt
{
	char	*hostname;
	char	*username;
	char	*color;
}	t_prompt;

typedef enum s_colors
{
	DEFAULT	= 0,
	GRAY	= 30,
	RED		= 31,
	GREEN	= 32,
	YELLOW	= 33,
	BLUE	= 34,
	PURPLE	= 35,
	CYAN	= 36,
	WHITE	= 37
}	t_colors;

// ============================PROTOTYPE========================================
// -------------main.c-------------
/* Execute the commands */
void	ft_execute(t_lexer *lex);

//-------------ft_prompt.c-------------
char	*ft_create_prompt(t_lexer *lex, char *color);

//-------------ft_utils.c-------------
char	**ft_copy_env(char **env);
void	ft_print_env(char **env, bool exp);
char	**ft_path_splitter(t_lexer *lex);

//-------------ft_lexer.c-------------
/* Conunt how much PIPE('|') or REDIRACTIONS('>' '>>' '<' '<<') in string */
int		ft_count_operators(char *string, char c);
/* TODO: DIVIDE (Split tokens) */
char	*ft_command_split(char *input, t_lexer *lex, int current_pos);
/* Create a matrix with the tokens from input */
char	**ft_tokenize(char *input, t_lexer *lex);

//-------------ft_little_executer.c-------------
/* strjoin with '/' in the middle */
char	*ft_strjoin_path(char const *s1, char const *s2);
/* Execute the command gived with arguments from lex */
void	ft_exec_path(t_lexer *lex);
void	sigint_handler(int sig);

//-------------ft_export.c-------------
/*
	0	Arguments: Display the env
	1+	Arguments: Set a Environment Variable
*/
void	ft_export(t_lexer *lex);

//-------------ft_builtin.c-------------
void	ft_chdir(t_lexer *lex);
void	ft_echo(t_lexer *lex);
/* Expand variables with their content */
char	*ft_expander(t_lexer *lex, char *str);

//-------------ft_free.c-------------
/* Free variable and set it to NULL */
void	ft_free(void **mem);
void	ft_free_matrix(char **matrix);
void	ft_free_matrix_len(char **matrix, int len);

//-------------ft_matrix_support.c-------------
/* Return the pointer to the found find string */
char	**ft_search_str_in_env(t_lexer *lex, char *find, int lenght_matrix);
int		ft_strlen_matrix(char **matrix);

//-------------ft_unset.c-------------
void	ft_unset(t_lexer *lex, bool exp);

//-------------ft_checks.c-------------
bool	ft_check_syntax_error(t_lexer *lex);
bool	ft_check_is_executable(t_lexer *lex);
bool	ft_check_is_variable(char *token);
int		ft_check_builtin(t_lexer *lex);

//-------------ft_checks.c-------------
int		ft_count_total_string(t_lexer *lex, char *input);
/* Count how much to malloc from a string */
int		ft_count_malloc_str(char *input);

//-------------ft_pipe.c-------------
int		ft_init_pipe(t_lexer *lex);
int		ft_pipe(t_lexer *lex, char **tokens, int old_fd, int more);

//-------------ft_tokens_args.c-------------
int		ft_tokens_args_len(t_lexer *lex);
char	**ft_tokens_args(t_lexer *lex);

//-------------ft_redirects.c-------------
void	ft_redirects(t_lexer *lex);

#endif

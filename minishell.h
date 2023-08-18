/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:54:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 14:40:41 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
	char 	**tokens;
	char	**global_tokens;
	char 	**paths;
	int		flags;
	char	**env_copy;
	int		lenght;
	char	*cwd;
	bool	absolute_path;
	int		pipe_num;
	t_ops	op;
	t_stds	stds;
	bool	can_return;
	int		return_value;
	int		current_pipe;
	int		current_redirect;
	char	**args;
	bool	is_executing;
}	t_lexer;

typedef	struct s_prompt
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

//main.c
void		ft_execute(t_lexer *lex);
bool	ft_check_is_variable(char	*token);

//ft_prompt.c
char	*ft_create_prompt_username(t_lexer *lex, char *color);
// void	ft_clear_screen(void);

//ft_utils.c
void	ft_print_env(char **env, bool exp);
int		ft_count_total_string(t_lexer *lex, char *input);
int		ft_count_malloc_str(char *input);
char	**ft_path_splitter(t_lexer *lex);
//ft_lexer.c
char	*ft_double_quote_control(char *input, char **matrix,int y, int x);
int		ft_count_operators(char *string, char c);
char	*ft_command_split(char *input, t_lexer *lex, int current_pos);
char	**ft_tokenize(char *input, t_lexer *lex);
//ft_little_executer.c
char	*ft_strjoin_path(char const *s1, char const *s2);
void	ft_exec_path(t_lexer *lex);
// bool	ft_check_command(t_lexer *lex);
void	sigint_handler();
bool	ft_path_try(t_lexer *lex);
//ft_export.c
void	ft_export(t_lexer *lex);
char	**ft_copy_env(char **env);
//ft_builtin.c
void	ft_chdir(t_lexer *lex);
void	ft_echo(t_lexer *lex);
char	*ft_expander(t_lexer *lex, char *str);
// void	ft_token_expander(t_lexer *lex);
//ft_free.c
void	ft_free(void **mem);
void	ft_free_matrix(char **matrix);
//ft_matrix_support.c
char	**ft_search_str_in_matrix(t_lexer *lex,char *str, int lenght_matrix);
int		ft_strlen_matrix (char **matrix);
//ft_unset.c
void	ft_unset(t_lexer *lex, bool exp);
//ft_checks.c
bool	ft_check_syntax_error(t_lexer *lex);
bool	ft_check_is_executable(t_lexer *lex);
bool	ft_check_is_variable(char	*token);
int		ft_check_builtin(t_lexer *lex);
//ft_pipe.c
int		ft_len_matrix_shell(t_lexer *lex);
char	**ft_matrix_shell(t_lexer *lex);
int		ft_pipe(t_lexer *lex, char **tokens, int old_fd, int more);
//ft_redirects.c
void	ft_redirects(t_lexer *lex);

#endif

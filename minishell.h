/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:54:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/04 15:26:59 by cschiavo         ###   ########.fr       */
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
# include "libft/libft.h"
# include <signal.h>	
# include <stdbool.h>
# include <term.h>
# include <sys/types.h>
# include <curses.h>
# include <sys/wait.h>

typedef struct s_lexer
{
	char 	**tokens;
	char 	**paths;
	bool	is_builtin;
	int		flags;
	char	*clean_comand;
	char	**new_env;
	char	**env_copy;
	int		lenght;
	char	*cwd;
}	t_lexer;

typedef	struct s_prompt
{
	char	*hostname;
	char	*cwd;
	char	*username;
	/* data */
}	t_prompt;

//main.c
char	**ft_search_str_in_matrix(t_lexer *lex,char *str, int lenght_matrix);
void	ft_free_matrix(char **matrix);
bool	ft_check_is_variable(char	*token);

//ft_prompt.c
char	*ft_create_prompt_username(void);
// void	ft_clear_screen(void);

//ft_utils.c
void	ft_print_env(char **env);
int		ft_strlen_matrix (char **matrix);
int		ft_count_total_string(char *input, char c);
int		ft_count_malloc_str(char *input);
char	**ft_path_splitter(t_lexer *lex);
//ft_clean_input.c
int	ft_count_input(char *input);
//ft_lexer.c
char	*ft_double_quote_control(char *input, char **matrix,int y, int x);
char	*ft_command_split(char *input, t_lexer *lex);
char	**ft_tokenize(char *input, t_lexer *lex);
char	**ft_path_splitter();
//ft_little_executer.c
char	*ft_strjoin_path(char const *s1, char const *s2);
void	ft_exec_path(t_lexer *lex);
// bool	ft_check_command(t_lexer *lex);
void	sigint_handler();
bool	ft_path_try(t_lexer *lex);
//ft_export.c
char	**ft_recreate_matrix(t_lexer *lex);
char	**ft_dup_matrix(char **env, t_lexer *lex);
char	**ft_copy_env(char **env);
char	**ft_unset(t_lexer *lex);
//ft_builtin.c
void	ft_chdir(t_lexer *lex);
void	ft_echo(t_lexer *lex);
char	*ft_expander(t_lexer *lex, char *str);
void	ft_token_expander(t_lexer *lex);

#endif

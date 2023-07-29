/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:54:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/29 18:46:20 by cschiavo         ###   ########.fr       */
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

typedef struct s_lexer
{
	char **tokens;
	char **paths;

}	t_lexer;

//ft_prompt.c
void	ft_create_prompt_username(void);
// void	ft_clear_screen(void);

//ft_utils.c
void	ft_print_env(char **env);
bool	ft_perror(char *str);
int	ft_strlen_matrix (char **matrix);
//ft_clean_input.c
int	ft_count_input(char *input);

#endif
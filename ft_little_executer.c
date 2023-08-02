/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_little_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:50:19 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/02 18:01:39 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//questo e' uno strjoin modificato per unire i path
char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	
	while(s1[i])
	{
		res[i] =s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while(s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return(res);
}

// questa funzione prova i path in bruteforce
void	ft_exec_path(t_lexer *lex, char **env, int n)
{
	char *path_try;
	int	i;
	pid_t pid;
	pid = fork();

	i = 0;
	if (n == 1)
	{
		i = ft_strlen_matrix(lex->paths);
		while(i--)
		{
			path_try = ft_strjoin_path(lex->paths[i],lex->tokens[0]);
			if (!access(path_try, F_OK))
			{
				if (pid == 0)
				{
					execve(path_try, lex->tokens, env);
					exit (1);
				}
				waitpid(pid, 0, 0);
			}
		}
	}
	else
	{
		i = ft_strlen_matrix(lex->paths);
		while(i--)
		{
			path_try = ft_strjoin_path(lex->paths[i],lex->clean_comand);
			if (!access(path_try, F_OK))
			{
				if (pid == 0)
				{	
					execve(path_try, lex->tokens, env);
					exit (1);
				}
				waitpid(pid, 0, 0);
			}
		}
	}
}
//"e""c"h"o"ciao "mo'n'd"

bool	ft_check_command(t_lexer *lex)
{
	int	x;
	int	i;
	int count_single_quote;
	char *path_try;
	int	j;

	x = 0;
	i = 0;
	count_single_quote = 1;
	while(lex->tokens[x][i])
	{
		if(lex->tokens[x][i] == 39 || lex->tokens[x][i] == 34)
		{
			count_single_quote = 0;
			while(lex->tokens[x][i])
			{
				if (lex->tokens[x][i] == 39 || lex->tokens[x][i] == 34)
				{
					count_single_quote++;
				}
				i++;		
			}
		}
		i++;
	}
	if(count_single_quote % 2 == 0)
	{
		lex->clean_comand = malloc(sizeof(char) * ft_strlen(lex->tokens[x] - count_single_quote) + 1);
		i = 0;
		j = 0;
		while(lex->tokens[x][i])
		{
			if(lex->tokens[x][i] != 39 && lex->tokens[x][i] != 34)
			{
				lex->clean_comand[j] = lex->tokens[x][i];
				j++;
			}
			i++;
		}
		lex->clean_comand[j] = '\0';
	}
	i = 0;
	if (count_single_quote % 2 == 0)
	{
		i = ft_strlen_matrix(lex->paths);
		while(i--)
		{
			path_try = ft_strjoin_path(lex->paths[i],lex->clean_comand);
			if (!access(path_try, F_OK))
				return(1);
		}
	}
	return(0);
}
void	sigint_handler()
{
	// t_prompt  *prompt;
	rl_on_new_line();
	write(1,"\n", 1);
	// rl_replace_line("\n",0);
}
bool ft_path_try(t_lexer *lex)
{
	int	i;
	char *path_try;

	i = 0;
	i = ft_strlen_matrix(lex->paths);
	while(i--)
	{
		path_try = ft_strjoin_path(lex->paths[i],lex->tokens[0]);
		if (!access(path_try, F_OK))
			return(1);
	}
	return (0);
}
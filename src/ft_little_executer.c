/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_little_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:50:19 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/09 19:53:22 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_prepare_in_and_out()
{
	
}
// questa funzione prova i path in bruteforce
void	ft_exec_path(t_lexer *lex)
{
	char *path_try;
	int	i;
	pid_t pid;

	i = 0;
	i = ft_strlen_matrix(lex->paths);
	/*
	se uno dei token == '|'
		allora tu fai dup2 di
	*/
	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, 0, 0);
		free(lex->op.pipe);
		free(lex->op.redirect);
		return ;
	}
	// if (lex->pipe_num > 0)
	// {
	// 		ft_pipe(lex);
	// }
	if (!lex->absolute_path)
	{
		while(i--)
		{
			path_try = ft_strjoin_path(lex->paths[i],lex->tokens[0]);
			if (!access(path_try, F_OK))
			{
				execve(path_try, lex->tokens, lex->env_copy);
				free(path_try);
				exit (0);
			}
			free(path_try);
		}
	}
	else
	{
		execve(lex->tokens[0], lex->tokens, lex->env_copy);
		exit (0);
	}
}
void	sigint_handler()
{
	rl_on_new_line();
	write(1,"\n", 1);
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
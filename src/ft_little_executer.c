/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_little_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:50:19 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 10:38:30 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_exec_path_child(t_lexer *lex)
{
	char	*path_try;
	int		i;

	if (lex->paths && !lex->absolute_path)
	{
		i = ft_strlen_matrix(lex->paths);
		while (i--)
		{
			path_try = ft_strjoin_path(lex->paths[i], lex->args[0]);
			if (!access(path_try, F_OK))
			{
				execve(path_try, lex->args, lex->env_copy);
				free(path_try);
				break ;
			}
			free(path_try);
		}
	}
	else
		execve(lex->args[0], lex->args, lex->env_copy);
	lex->return_value = 126;
}

void	ft_exec_path(t_lexer *lex)
{
	pid_t	pid;
	int		status;

	pid = 0;
	if (lex->op.n_pipe <= 0)
	{
		lex->is_executing = true;
		pid = fork();
		if (pid == -1)
			lex->return_value = 1;
		if (pid != 0)
		{
			waitpid(pid, &status, 0);
			lex->return_value = (unsigned char)WEXITSTATUS(status);
			lex->is_executing = false;
			ft_free((void **)&lex->op.pipe);
			ft_free((void **)&lex->op.redirect);
			return ;
		}
	}
	ft_exec_path_child(lex);
}

void	sigint_handler(int sig)
{
	rl_on_new_line();
	write(1, "\n", 1);
	(void)sig;
}

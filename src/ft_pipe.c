/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:28:01 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 18:43:48 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_lexer *lex)
{
	ft_free((void **)&lex->cwd);
	ft_free((void **)&lex->op.pipe);
	ft_free((void **)&lex->op.redirect);
	lex->tokens = lex->global_tokens;
	ft_free_matrix(lex->tokens);
	ft_free_matrix(lex->paths);
	ft_free_matrix(lex->env_copy);
	exit (lex->return_value);
}

int	ft_init_pipe(t_lexer *lex)
{
	pid_t	pid;
	int		i;

	pid = 0;
	lex->is_executing = true;
	i = 0;
	pid = fork();
	if (pid == -1)
		lex->return_value = 1;
	if (pid != 0)
	{
		waitpid(pid, &i, 0);
		lex->return_value = (unsigned char)WEXITSTATUS(i);
		lex->is_executing = false;
		ft_free((void **)&lex->op.pipe);
		ft_free((void **)&lex->op.redirect);
		return (0);
	}
	lex->lenght = 0;
	if (ft_pipe(lex, lex->tokens, 0, 0) != -1)
		ft_child(lex);
	lex->args = ft_tokens_args(lex);
	return (1);
}

int	ft_pipe_fd(t_lexer *lex, char **tokens, int old_fd, t_pv *pv)
{
	lex->tokens = tokens;
	if (!tokens || !lex->env_copy)
		return (0);
	if (!tokens[0])
	{
		ft_perror("bash: Missing command\n");
		return (1);
	}
	if (pipe(pv->pipe_fd) == -1)
		return (1);
	if (pv->more)
		if (dup2(old_fd, STDIN_FILENO) < 0)
			return (2);
	if (dup2(pv->pipe_fd[1], STDOUT_FILENO) < 0)
		return (3);
	close(pv->pipe_fd[1]);
	if (lex->current_pipe >= lex->op.n_pipe)
		dup2(lex->stds.stdout, STDOUT_FILENO);
	if (lex->op.n_redirect > 0)
		ft_redirects(lex);
	return (-1);
}

int	ft_pipe(t_lexer *lex, char **tokens, int old_fd, int more)
{
	t_pv	pv;

	pv.more = more;
	pv.i = ft_pipe_fd(lex, tokens, old_fd, &pv);
	if (pv.i != -1)
		return (pv.i);
	pv.pid1 = fork();
	if (pv.pid1 < 0)
	{
		ft_perror("ERROR: pipe can't store fds\n");
		return (1);
	}
	if (pv.pid1 == 0)
		return (-1);
	dup2(lex->stds.stdin, STDIN_FILENO);
	dup2(lex->stds.stdout, STDOUT_FILENO);
	waitpid(pv.pid1, &pv.i, 0);
	lex->return_value = (unsigned char)WEXITSTATUS(pv.i);
	lex->current_pipe++;
	pv.i = lex->op.pipe[lex->current_pipe - 1] - lex->lenght + 1;
	lex->lenght += pv.i;
	if (lex->op.pipe[lex->current_pipe - 1] != -1)
		return (ft_pipe(lex, &tokens[pv.i], pv.pipe_fd[0], more + 1));
	return (0);
}

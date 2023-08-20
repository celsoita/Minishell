/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:40:34 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 20:50:39 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_reset(t_lexer *lex)
{
	if (lex->stds.stdin != STDIN_FILENO)
		dup2(lex->stds.stdin, STDIN_FILENO);
	if (!access(".temp", F_OK))
	{
		if (!fork())
		{
			lex->args = malloc(sizeof(char *) * (2 + 1));
			lex->args[0] = "/usr/bin/rm";
			lex->args[1] = ".temp";
			lex->args[2] = NULL;
			execve("/usr/bin/rm", lex->args, lex->env_copy);
			ft_free((void **)&lex->cwd);
			ft_free((void **)&lex->op.pipe);
			ft_free((void **)&lex->op.redirect);
			lex->tokens = lex->global_tokens;
			ft_free_matrix(lex->tokens);
			ft_free_matrix(lex->args);
			ft_free_matrix(lex->paths);
			ft_free_matrix(lex->env_copy);
			exit (lex->return_value);
		}
		waitpid(-1, NULL, 0);
	}
	dup2(lex->stds.stdin, STDIN_FILENO);
	dup2(lex->stds.stdout, STDOUT_FILENO);
}

void	ft_execute_continue(t_lexer *lex)
{
	if (ft_check_is_executable(lex) && ft_check_syntax_error(lex))
		ft_exec_path(lex);
	else if (lex->paths && ft_strchr(lex->args[0], '/'))
	{
		if (!access(lex->args[0], F_OK) && access(lex->args[0], X_OK))
		{
			ft_perror("%s: Permission denied\n", lex->args[0]);
			lex->return_value = 126;
		}
		else
		{
			ft_perror("%s: No such file or directory\n", lex->args[0]);
			lex->return_value = 127;
		}
	}
	else if (lex->paths && lex->args[0] != NULL)
	{
		ft_perror("%s: not a command\n", lex->args[0]);
		lex->return_value = 127;
	}
}

bool	ft_execute_command(t_lexer *lex)
{
	if (lex->args && lex->args[0])
	{
		if (ft_check_builtin(lex))
		{
			lex->return_value = ft_exec_builtin(lex);
			if (lex->can_return == true)
			{
				lex->tokens = lex->global_tokens;
				return (1);
			}
		}
		else
			ft_execute_continue(lex);
	}
	else
	{
		ft_perror("bash: Missing command\n");
		lex->return_value = 1;
	}
	ft_free_matrix(lex->args);
	return (0);
}

void	ft_execute_free(t_lexer *lex)
{
	if (lex->is_executing)
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
	ft_execute_reset(lex);
}

void	ft_execute(t_lexer *lex)
{
	lex->global_tokens = lex->tokens;
	if (lex->op.n_pipe > 0)
	{
		if (!ft_init_pipe(lex))
			return ;
	}
	else
	{
		lex->args = ft_tokens_args(lex);
		if (lex->op.n_redirect > 0)
			ft_redirects(lex);
	}
	if (ft_execute_command(lex))
		return ;
	ft_execute_free(lex);
}

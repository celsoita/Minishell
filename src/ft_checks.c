/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:07:10 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 11:44:09 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_syntax_error(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex->args[0][i])
	{
		if (lex->args[0][i] == '\'' || lex->args[0][i] == '"')
			return (0);
		i++;
	}
	return (1);
}

bool	ft_check_is_executable_path(t_lexer *lex)
{
	int		i;
	char	*path_try;

	i = 0;
	if (lex->paths)
	{
		while (lex->paths[i])
		{
			path_try = ft_strjoin_path(lex->paths[i], lex->args[0]);
			if (!access(path_try, F_OK | X_OK))
			{
				free(path_try);
				return (1);
			}
			i++;
			free(path_try);
		}
	}
	return (0);
}

bool	ft_check_is_executable(t_lexer *lex)
{
	if (access(lex->args[0], F_OK) && !lex->paths)
	{
		ft_perror("%s: No such file or directory\n", lex->args[0]);
		lex->return_value = 127;
		return (0);
	}
	lex->absolute_path = false;
	if (ft_check_is_executable_path(lex))
		return (1);
	if (!access(lex->args[0], F_OK | X_OK))
	{
		lex->absolute_path = true;
		return (1);
	}
	return (0);
}

bool	ft_check_is_variable(char *token)
{
	int	x;

	x = 0;
	while (token[x])
	{
		if (token[x] == '$')
			return (0);
		if (token[x] == '=' && token[x + 1] != 32)
			return (1);
		x++;
	}
	return (0);
}

int	ft_check_builtin(t_lexer *lex)
{
	lex->flags = 0;
	if (!ft_strcmp(lex->tokens[0], "echo"))
		lex->flags = 1;
	if (!ft_strcmp(lex->tokens[0], "cd"))
		lex->flags = 2;
	if (!ft_strcmp(lex->tokens[0], "pwd"))
		lex->flags = 3;
	if (!ft_strcmp(lex->tokens[0], "export"))
		lex->flags = 4;
	if (!ft_strcmp(lex->tokens[0], "unset"))
		lex->flags = 5;
	if (!ft_strcmp(lex->tokens[0], "env"))
		lex->flags = 6;
	if (!ft_strcmp(lex->tokens[0], "exit"))
		lex->flags = 7;
	return (lex->flags);
}

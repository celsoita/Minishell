/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:07:10 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 12:04:35 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_syntax_error(t_lexer *lex)
{
	int	i;

	i = 0;
	while(lex->tokens[0][i])
	{
		if (lex->tokens[0][i] == '\'' || lex->tokens[0][i] == '"')
			return (0);
		i++;
	}
	return (1);
}

bool	ft_check_is_executable(t_lexer *lex)
{
	int	i;
	char	*path_try;

	if (!lex->paths)
	{
		ft_perror("%s: No such file or directory\n", lex->tokens[0]);
		return (0);
	}
	lex->absolute_path = false;
	i = 0;
	while (lex->paths[i])
	{
		path_try = ft_strjoin_path(lex->paths[i], lex->tokens[0]);
		if (!access(path_try, F_OK))
		{
			free(path_try);
			return (1);
		}
		i++;
		free(path_try);
	}
	if (!access(lex->tokens[0], F_OK))
	{
		lex->absolute_path = true;
		return (1);
	}
	return (0);
}

bool	ft_check_is_variable(char	*token)
{
	int	x;

	x = 0;
	while(token[x])
	{
		if(token[x] == '$')
			return(0);
		if(token[x] == '=' && token[x + 1] != 32)
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
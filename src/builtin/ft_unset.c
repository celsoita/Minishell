/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:01:04 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 11:45:14 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_free(t_lexer *lex, int unset_variables, int lenght, int y)
{
	char	**return_search;

	return_search = ft_search_str_in_env(lex, lex->args[y], lenght);
	if (return_search && *return_search)
	{
		ft_free((void **)&*return_search);
		unset_variables++;
	}
	return_search = 0;
}

void	ft_unset_update(t_lexer *lex, int unset_variables, int lenght)
{
	char	**matrix;
	int		x;
	int		y;

	matrix = malloc(sizeof(char *) * (lenght - unset_variables + 1));
	y = -1;
	x = 0;
	while (++y < lenght - unset_variables)
	{
		while (!lex->env_copy[y + x] && y + x < lenght)
			x++;
		matrix[y] = ft_strdup(lex->env_copy[y + x]);
	}
	matrix[y] = NULL;
	ft_free_matrix_len(lex->env_copy, lenght);
	x = -1;
	while (lex->args[++x])
	{
		if (!ft_strncmp(lex->args[x], "PATH", 4))
		{
			ft_free_matrix(lex->paths);
			lex->paths = NULL;
		}
	}
	lex->env_copy = matrix;
}

/* When unsetting PATH: free lex->paths */
void	ft_unset(t_lexer *lex, bool exp)
{
	int		lenght;
	int		y;
	int		num_token;
	int		unset_variables;

	if (!lex->args[1])
		return ;
	lenght = ft_strlen_matrix(lex->env_copy);
	num_token = ft_strlen_matrix(lex->args);
	y = 1;
	unset_variables = 0;
	while (y < num_token)
	{
		if (!ft_charinstring('=', lex->args[y]) || \
			(exp && ft_charinstring('=', lex->args[y])))
			ft_unset_free(lex, unset_variables, lenght, y);
		else if (!exp)
			ft_perror("unset: `%s': not a valid identifier\n", lex->args[y]);
		y++;
	}
	if (!unset_variables)
		return ;
	ft_unset_update(lex, unset_variables, lenght);
}

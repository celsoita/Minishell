/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:01:04 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/07 12:36:08 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_lexer *lex, bool exp)
{
	int	lenght;
	int	y;
	int	x;
	char	**return_search;
	int	num_token;
	int	unset_variables;
	char	**matrix;

	if (!lex->tokens[1])
		return ;
	lenght = ft_strlen_matrix(lex->env_copy);
	num_token = ft_strlen_matrix(lex->tokens);
	y = 1;
	unset_variables = 0;
	while (y < num_token)
	{
		if (!ft_charinstring('=', lex->tokens[y]) || (exp && ft_charinstring('=', lex->tokens[y])))
		{
			return_search = ft_search_str_in_matrix(lex,lex->tokens[y], lenght);
			if (return_search && *return_search)
			{
				free(*return_search);
				*return_search = NULL;
				unset_variables++;
			}
			return_search = 0;
		}
		else if (!exp)
			ft_perror("unset: `%s': not a valid identifier\n", lex->tokens[y]);
		y++;
	}
	if (!unset_variables)
		return ;
	matrix = malloc(sizeof(char *) * (lenght - unset_variables + 1));
	y = 0;
	x = 0;
	while (y < lenght - unset_variables)
	{
		while (!lex->env_copy[y + x] && y + x < lenght)
			x++;
		matrix[y] = ft_strdup(lex->env_copy[y + x]);
		y++;
	}
	matrix[y] = NULL;
	ft_free_matrix(lex->env_copy);
	x = 0;
	while (lex->tokens[x])
	{
		if (!ft_strncmp(lex->tokens[x], "PATH", 4))
		{
			ft_free_matrix(lex->paths);
			lex->paths = 0;
		}
		x++;
	}
	lex->env_copy = matrix;
}

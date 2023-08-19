/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:56:06 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/19 15:16:35 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_search_str_in_matrix(t_lexer *lex, char *str, int lenght_matrix)
{
	int	y;
	int	x;

	if (!str)
		return (NULL);
	if (lenght_matrix == 0)
		lenght_matrix = ft_strlen_matrix(lex->env_copy);
	y = 0;
	while (y < lenght_matrix)
	{
		if (lex->env_copy[y])
		{
			x = 0;
			while (str[x] == lex->env_copy[y][x] && lex->env_copy[y][x] \
			!= '=' && lex->env_copy[y][x])
				x++;
			if (!ft_isalnum(str[x]) && lex->env_copy[y][x] == '=')
				return (&lex->env_copy[y]);
		}
		y++;
	}
	return (NULL);
}

int	ft_strlen_matrix(char **matrix)
{
	int	y;

	if (!matrix)
		return (0);
	y = 0;
	while (matrix[y])
		y++;
	return (y);
}

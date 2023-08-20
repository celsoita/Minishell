/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:56:06 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 10:54:59 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_search_str_in_env(t_lexer *lex, char *find, int lenght_matrix)
{
	int	y;
	int	x;

	if (!find)
		return (NULL);
	if (lenght_matrix == 0)
		lenght_matrix = ft_strlen_matrix(lex->env_copy);
	y = 0;
	while (y < lenght_matrix)
	{
		if (lex->env_copy[y])
		{
			x = 0;
			while (find[x] == lex->env_copy[y][x] && lex->env_copy[y][x] \
			!= '=' && lex->env_copy[y][x])
				x++;
			if (!ft_isalnum(find[x]) && lex->env_copy[y][x] == '=')
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

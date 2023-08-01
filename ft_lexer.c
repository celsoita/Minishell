/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:45:02 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/01 13:47:44 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_double_quote_control(char *input, char **matrix,int y, int x)
{
	y++;
	if(input[y] !=  '"')
	{
		matrix[x] = ft_substr(input,y-1,ft_count_malloc_str(&input[y - 1]));
	}
	return(matrix[x]);
}

//questa funzione divide in piu' stringhe  l' input

char	**ft_tokenize(char *input)
{
	int	x;
	int	y;
	int	num_string;
	char **matrix;

	x = 0;
	y = 0;
	num_string = ft_count_total_string(input, 32);
	matrix = malloc((num_string + 1) * sizeof(char *));
	while (num_string--)
	{
		while (input[y])
		{
			
			if (input[y] != 32)
			{
				if (input[y] == '"')
				{
					matrix[x] = ft_double_quote_control(input,matrix,y,x);
					y += ft_count_malloc_str(&input[y]);
					break ;
				}
				else
				{
					matrix[x] = ft_substr(input, y, ft_count_malloc_str(&input[y]));
					y += ft_count_malloc_str(&input[y]);
					break ;
				}
			}
			y++;
		}
	x++;
	}
	matrix[x] = 0;
	return (matrix);
}

/*
	serve una funzione per splittare i path e metterli in una
	 matrix , poi dopo successivamente bisogna aggiungere il path con il comando e testare
	 con access se il comando esiste e poi in futuro passare tutto a execve

*/
char	**ft_path_splitter()
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	return(paths);
}
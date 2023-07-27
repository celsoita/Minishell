/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:26:24 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/27 17:54:17 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_perror(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_print_env(char **env)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(env[y])
	{
		printf("%s\n",env[y]);
		y++;
	}
}

int	ft_strlen_matrix (char **matrix)
{
	int	y;

	y = 0;
	while(matrix[y])
		y++;
	return (y);
}
/*
// int	ft_count_clean_input (char *input)
// {
// 	int	i;
// 	int	space_extra;

// 	i = 0;
// 	space_extra = 0;
// 	while(input[i] == ' ')
// 		i++;
// 	while (input[i] != ' ' && input[i] != '\0')
// 	{
// 		if(input[i] == '"')
// 		{
// 			i++;
// 			while(input[i] != '"' && input[i] != '\0')
// 				i++;
// 		}
// 		if (input[i] == ' ')
// 			space_extra++;
// 		i++;
// 	}
// 	return (i - space_extra);
// }
*/
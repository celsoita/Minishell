/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:26:24 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/02 19:14:27 by cschiavo         ###   ########.fr       */
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
	int	y;
	int	i;

	y = 0;
	i = 0;
	i = ft_strlen_matrix(env);
	while(y < i)
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

//str di es :   echo -n  "ciao mondo"|" banana" 
// questa funzione conta il numero totale  di stringhe
int	ft_count_total_string(char *input, char c)
{
	int	i;
	int	ns;

	i = 0;
	ns = 0;
	//esempio : "c"o""m""a""n"do"
	while (input[i] != 0)
	{
		if (input[i] != c)
		{
			if (input[i] == '"')
			{
				i++;
				while(input[i] != '"' && input[i])
					i++;
				if (input[i])
					i++;
				if (input[i] == ' ' || input[i] == 0)
					ns++;
			}
			else if (input[i] == '\'')
			{
				i++;
				while(input[i] != '\'' && input[i])
					i++;
				if (input[i])
					i++;
				if (input[i] == ' ' || input[i] == 0)
					ns++;
			}
			else
			{
				ns++;
				while (input[i] != c && input[i] != '\0')
					i++;
			}
		}
		if (input[i] != '\0')
			i++;
	}
	return (ns);

}
//questa funzione serve a contare il numero necessario per malloccare la uso nella mia split modificata
int	ft_count_malloc_str(char *input)
{
	int	i;

	i = 0;
	while (input[i] == 32)
		i++;
	if (input[i] == 124)
		return (1);
	while (input[i] != 32 && input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while(input[i] != '"' && input[i])
				i++;
			return(i+1);
		}
		if (input[i] == 32)
			return (i);
		i++;
	}
	return (i);	
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
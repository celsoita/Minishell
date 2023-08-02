/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:52:36 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/02 15:14:40 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funzione che duplica matrice e aggiunge stringhe passate
char	**ft_dup_matrix(char **env, t_lexer *lex)
{
	int	num_string;
	int	x;
	int	len_env;
	char	**matrix_env;
	int	i;
	int	y;
	int	dimension_token;
	int	count;
	matrix_env = 0;
	y = 1;
	 dimension_token = ft_strlen_matrix(lex->tokens);
	count = 0; 
	while(y < dimension_token)
	{
		if (ft_check_is_variable(lex->tokens[y]) == 1)
			count++;
		y++;
	}
	y = 1;
	while(y < dimension_token)
	{
		if (ft_check_is_variable(lex->tokens[y]) == 1)
		{
			num_string = 0;
			len_env = 0;
			num_string = ft_strlen_matrix(env);
			matrix_env = malloc (sizeof(char *) * (num_string + count + 1));
			i = 0;
			x = 0;
			while(i < num_string + count)
			{
				if (i >= num_string)
				{
					while (ft_check_is_variable(lex->tokens[y]) == 0)
						y++;
					x = 0;
					len_env = ft_strlen(lex->tokens[y]);
					matrix_env[i] = malloc(sizeof(char *) * len_env + 1);
					while(x < len_env)
					{
						matrix_env[i][x] = lex->tokens[y][x];
						x++;
					}
					y++;
					matrix_env[i][x] = '\0';
				}
				else
				{

					len_env = ft_strlen(env[i]);
					matrix_env[i] = malloc(sizeof(char *) * ft_strlen(env[i]) + 1);
					
					while(x < len_env)
					{
						matrix_env[i][x] = env[i][x];
						x++;
					}
					matrix_env[i][x] = '\0';
					x = 0;
				}
				i++;
			}
		}
		y++;
	}
	matrix_env[i] = NULL;
	ft_free_matrix(lex->env_copy);
	lex->env_copy = NULL;
	return (matrix_env);
}
//funzione che mi copia una matrice
char	**ft_copy_env(char **env)
{
	int	num_string;
	int	x;
	int	leng_string;
	int	y;
	char **matrix_env;
	
	num_string = ft_strlen_matrix(env);
	matrix_env = malloc(sizeof(char *) * num_string + 1);

	y = 0;
	leng_string = 0;
	while(y < num_string)
	{
		x = 0;
		leng_string = ft_strlen(env[y]);
		matrix_env[y] = malloc(sizeof(char *) * leng_string + 1);
		while(x < leng_string)
		{
			matrix_env[y][x] = env[y][x];
			x++;
		}
		matrix_env[y][x] = '\0';
		y++;
	}
	matrix_env[y] = NULL;
	return(matrix_env);
}
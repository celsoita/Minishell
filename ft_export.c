/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:52:36 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/04 10:00:21 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funzione che duplica matrice e aggiunge stringhe passate
char	**ft_dup_matrix(char **env, t_lexer *lex)
{
	char	**matrix_env;
	int		len_env;
	int		num_string;
	int		dimension_token;
	int		count;
	int		x;
	int		i;
	int		y;

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
	char	**matrix_env;
	int		num_string;
	int		leng_string;
	int		x;
	int		y;
	
	num_string = ft_strlen_matrix(env);
	matrix_env = malloc(sizeof(char *) * (num_string + 1));

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

char **ft_unset(t_lexer *lex)
{
	int	lenght;
	int	y;
	int	x;
	char	**return_search;
	int	num_token;
	int	unset_variables;
	char	**matrix;

	if (!lex->tokens[1])
		return (lex->env_copy);
	lenght = 0;
	lenght = ft_strlen_matrix(lex->env_copy);
	num_token = ft_strlen_matrix(lex->tokens);
	y = 1;
	unset_variables = 0;
	while (y < num_token)
	{
		return_search = ft_search_str_in_matrix(lex,lex->tokens[y], lenght);
		if (return_search && *return_search)
		{
			free(*return_search);
			*return_search = NULL;
			unset_variables++;
		}
		return_search = 0;
		y++;
	}
	if (!unset_variables)
		return (lex->env_copy);
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
	return (matrix);
}

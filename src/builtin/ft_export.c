/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:52:36 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 10:47:38 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_lexer *lex)
{
	char	**matrix_env;
	int		len_env;
	int		num_string;
	int		dimension_token;
	int		count;
	int		x;
	int		i;
	int		y;

	if (lex->args[1] == NULL)
	{
		ft_print_env(lex->env_copy, true);
		return ;
	}
	ft_unset(lex, true);
	matrix_env = 0;
	i = 0;
	x = 0;
	y = 1;
	dimension_token = ft_strlen_matrix(lex->args);
	count = 0;
	while (y < dimension_token)
	{
		if (ft_check_is_variable(lex->args[y]) == 1)
			count++;
		y++;
	}
	y = 1;
	while (y < dimension_token)
	{
		if (ft_check_is_variable(lex->args[y]) == 1)
		{
			num_string = 0;
			len_env = 0;
			num_string = ft_strlen_matrix(lex->env_copy);
			matrix_env = malloc (sizeof(char *) * (num_string + count + 1));
			i = 0;
			x = 0;
			while (i < num_string + count)
			{
				if (i >= num_string)
				{
					while (ft_check_is_variable(lex->args[y]) == 0)
						y++;
					x = 0;
					len_env = ft_strlen(lex->args[y]);
					matrix_env[i] = malloc(sizeof(char *) * len_env + 1);
					while (x < len_env)
					{
						matrix_env[i][x] = lex->args[y][x];
						x++;
					}
					y++;
					matrix_env[i][x] = '\0';
				}
				else
				{
					len_env = ft_strlen(lex->env_copy[i]);
					matrix_env[i] = malloc(sizeof(char *) * ft_strlen(lex->env_copy[i]) + 1);

					while (x < len_env)
					{
						matrix_env[i][x] = lex->env_copy[i][x];
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
	if (matrix_env)
	{
		matrix_env[i] = NULL;
		ft_free_matrix(lex->env_copy);
		lex->env_copy = NULL;
		lex->env_copy = matrix_env;
	}
	x = 0;
	while (lex->args[x])
	{
		if (!ft_strncmp(lex->args[x], "PATH", 4))
		{
			ft_free_matrix(lex->paths);
			lex->paths = ft_path_splitter(lex);
		}
		x++;
	}
}

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
	while (y < num_string)
	{
		x = 0;
		leng_string = ft_strlen(env[y]);
		matrix_env[y] = malloc(sizeof(char *) * leng_string + 1);
		while (x < leng_string)
		{
			matrix_env[y][x] = env[y][x];
			x++;
		}
		matrix_env[y][x] = '\0';
		y++;
	}
	matrix_env[y] = NULL;
	return (matrix_env);
}

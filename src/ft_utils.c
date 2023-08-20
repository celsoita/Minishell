/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:26:24 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 13:32:30 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_env(char **env)
{
	char	**matrix_env;
	int		num_string;
	int		y;

	num_string = ft_strlen_matrix(env);
	matrix_env = malloc(sizeof(char *) * (num_string + 1));
	y = 0;
	while (y < num_string)
	{
		matrix_env[y] = ft_strdup(env[y]);
		y++;
	}
	matrix_env[y] = NULL;
	return (matrix_env);
}

void	ft_print_env(char **env, bool exp)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	i = ft_strlen_matrix(env);
	while (y < i)
	{
		if (exp)
			printf("declare -x ");
		x = 0;
		while (env[y][x])
		{
			printf("%c", env[y][x]);
			if (exp && env[y][x] == '=')
				printf("\"");
			x++;
		}
		if (exp)
			printf("\"");
		printf("\n");
		y++;
	}
}

char	**ft_path_splitter(t_lexer *lex)
{
	char	*path;
	char	**res;

	res = NULL;
	path = ft_expander(lex, "PATH");
	if (path)
		res = ft_split(path, ':');
	free(path);
	return (res);
}

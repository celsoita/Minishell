/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:52:36 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 20:30:57 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_reset(t_lexer *lex, char **matrix_env, int i)
{
	if (matrix_env)
	{
		matrix_env[i] = NULL;
		ft_free_matrix(lex->env_copy);
		lex->env_copy = NULL;
		lex->env_copy = matrix_env;
	}
	i = 0;
	while (lex->args[i])
	{
		if (!ft_strncmp(lex->args[i], "PATH", 4))
		{
			ft_free_matrix(lex->paths);
			lex->paths = ft_path_splitter(lex);
		}
		i++;
	}
}

bool	ft_export_init(t_lexer *lex, t_ev *ev)
{
	if (lex->args[1] == NULL)
	{
		ft_print_env(lex->env_copy, true);
		return (1);
	}
	ft_unset(lex, true);
	ev->matrix_env = 0;
	ev->i = 0;
	ev->x = 0;
	ev->y = 1;
	ev->dimension_token = ft_strlen_matrix(lex->args);
	ev->c = 0;
	while (ev->y < ev->dimension_token)
	{
		if (ft_check_is_variable(lex->args[ev->y]) == 1)
			ev->c++;
		ev->y++;
	}
	return (0);
}

void	ft_export_new(t_lexer *lex, t_ev *ev)
{
	while (ft_check_is_variable(lex->args[ev->y]) == 0)
		ev->y++;
	ev->x = 0;
	ev->len_env = ft_strlen(lex->args[ev->y]);
	ev->matrix_env[ev->i] = malloc(sizeof(char *) * ev->len_env + 1);
	while (ev->x < ev->len_env)
	{
		ev->matrix_env[ev->i][ev->x] = lex->args[ev->y][ev->x];
		ev->x++;
	}
	ev->y++;
	ev->matrix_env[ev->i][ev->x] = '\0';
}

void	ft_export(t_lexer *lex)
{
	t_ev	ev;

	if (ft_export_init(lex, &ev))
		return ;
	ev.y = 0;
	while (++ev.y < ev.dimension_token)
	{
		if (ft_check_is_variable(lex->args[ev.y]) == 1)
		{
			ev.num_str = 0;
			ev.len_env = 0;
			ev.num_str = ft_strlen_matrix(lex->env_copy);
			ev.matrix_env = malloc (sizeof(char *) * (ev.num_str + ev.c + 1));
			ev.x = 0;
			ev.i = -1;
			while (++ev.i < ev.num_str + ev.c)
			{
				if (ev.i >= ev.num_str)
					ft_export_new(lex, &ev);
				else
					ev.matrix_env[ev.i] = ft_strdup(lex->env_copy[ev.i]);
			}
		}
	}
	ft_export_reset(lex, ev.matrix_env, ev.i);
}

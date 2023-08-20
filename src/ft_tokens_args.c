/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:34:14 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 18:51:20 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_t_a_l_redirections(t_lexer *lex, int *i, int *lenght)
{
	int	n_temp;

	if (lex->tokens[(*i)][0] == '>' || lex->tokens[(*i)][0] == '<')
	{
		n_temp = 0;
		while (lex->op.redirect[n_temp] > -1)
		{
			if ((*i) + lex->lenght == lex->op.redirect[n_temp])
			{
				(*lenght)--;
				if (lex->tokens[(*i) + 1] != NULL)
					(*lenght)--;
				break ;
			}
			n_temp++;
		}
	}
}

int	ft_tokens_args_len(t_lexer *lex)
{
	int	i;
	int	lenght;
	int	n_temp;

	lenght = 0;
	i = 0;
	while (lex->tokens[i])
	{
		if (lex->tokens[i][0] == '|')
		{
			n_temp = 0;
			while (lex->op.pipe[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.pipe[n_temp])
					break ;
				n_temp++;
			}
			if (lex->op.pipe[n_temp] && i + lex->lenght == lex->op.pipe[n_temp])
				break ;
		}
		ft_t_a_l_redirections(lex, &i, &lenght);
		i++;
	}
	lenght += i;
	return (lenght);
}

int	ft_t_a_redirections(t_lexer *lex, int *i, int *n_temp)
{
	if (lex->tokens[(*i)][0] == '>' || lex->tokens[(*i)][0] == '<')
	{
		(*n_temp) = 0;
		while (lex->op.redirect[(*n_temp)] > -1)
		{
			if ((*i) + lex->lenght == lex->op.redirect[(*n_temp)])
			{
				(*i)++;
				if (lex->tokens[(*i)])
					(*i)++;
			}
			(*n_temp)++;
		}
	}
	if (lex->tokens[(*i)] == NULL)
		return (1);
	return (0);
}

int	ft_t_a_pipe(t_lexer *lex, int *i, int *n_temp)
{
	if (lex->tokens[(*i)][0] == '|')
	{
		(*n_temp) = 0;
		while (lex->op.pipe[(*n_temp)] > -1)
		{
			if ((*i) + lex->lenght == lex->op.pipe[(*n_temp)])
				return (1);
			(*n_temp)++;
		}
		if (lex->op.pipe[(*n_temp)] && \
			(*i) + lex->lenght == lex->op.pipe[(*n_temp)])
			return (1);
	}
	return (0);
}

char	**ft_tokens_args(t_lexer *lex)
{
	char	**matrix;
	int		i;
	int		len_matrix;
	int		n_temp;

	if (!lex->tokens)
		return (NULL);
	matrix = malloc(sizeof(char *) * (ft_tokens_args_len(lex) + 1));
	len_matrix = 0;
	i = 0;
	while (lex->tokens[i])
	{
		if (ft_t_a_redirections(lex, &i, &n_temp))
			break ;
		if (ft_t_a_pipe(lex, &i, &n_temp))
			break ;
		matrix[len_matrix] = ft_strdup(lex->tokens[i]);
		len_matrix++;
		i++;
	}
	matrix[len_matrix] = NULL;
	return (matrix);
}

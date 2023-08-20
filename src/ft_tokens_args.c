/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:34:14 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 11:34:46 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (lex->tokens[i][0] == '>' || lex->tokens[i][0] == '<')
		{
			n_temp = 0;
			while (lex->op.redirect[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.redirect[n_temp])
				{
					lenght -= 1;
					if (lex->tokens[i + 1] != NULL)
						lenght -= 1;
					break ;
				}
				n_temp++;
			}
		}
		i++;
	}
	lenght += i;
	return (lenght);
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
	// ft_perror("DEBUG1: LEN MATRIX SHELL(%d)\n", ft_tokens_args_len(lex)); // REMOVE
	len_matrix = 0;
	i = 0;
	while (lex->tokens[i])
	{
		if (lex->tokens[i][0] == '>' || lex->tokens[i][0] == '<')
		{
			n_temp = 0;
			while (lex->op.redirect[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.redirect[n_temp])
					i += 2;
				n_temp++;
			}
		}
		if (lex->tokens[i] == NULL)
			break ;
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
		matrix[len_matrix] = ft_strdup(lex->tokens[i]);
		// ft_perror("DEBUG: matrix[len(%d)](%s)\n", len_matrix, matrix[len_matrix]);	//REMOVE
		len_matrix++;
		i++;
	}
	matrix[len_matrix] = NULL;
	return (matrix);
}

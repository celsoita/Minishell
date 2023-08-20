/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:54:57 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 18:38:07 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_variables(char *string)
{
	int		i;
	int		variables_found;
	bool	in_quote[2];

	in_quote[0] = false;
	in_quote[1] = false;
	i = 0;
	variables_found = 0;
	while (string[i] && (!ft_charinstring(string[i], " \t") \
		|| in_quote[0] || in_quote[1]))
	{
		if (!in_quote[0] && !in_quote[1] && ft_charinstring(string[i], "|<>"))
			break ;
		if (!in_quote[1] && string[i] == '$')
			variables_found++;
		if (string[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (string[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		i++;
	}
	return (variables_found);
}

char	*ft_expand_exit_status(t_lexer *lex)
{
	char	*res;

	res = ft_itoa(lex->return_value);
	return (res);
}

/* Operators: '|' '>'('>>') '<'('<<') */
int	ft_count_operators(char *string, char c)
{
	int		i;
	int		ops_found;
	bool	in_quote[2];

	in_quote[0] = false;
	in_quote[1] = false;
	i = 0;
	ops_found = 0;
	while (string[i])
	{
		if (!in_quote[1] && !in_quote[0] && string[i] == c)
		{
			ops_found++;
			while (string[i] == string[i + 1])
				i++;
		}
		if (string[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (string[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		i++;
	}
	return (ops_found);
}

bool	ft_init_operations(t_lexer *lex, char *input, int *num_string)
{
	lex->op.n_pipe = ft_count_operators(input, '|');
	lex->op.n_redirect = ft_count_operators(input, '>');
	lex->op.n_redirect += ft_count_operators(input, '<');
	lex->op.pipe = malloc(sizeof(int) * (lex->op.n_pipe + 1));
	lex->op.pipe[lex->op.n_pipe] = -1;
	lex->op.redirect = malloc(sizeof(int) * (lex->op.n_redirect + 1));
	lex->op.redirect[lex->op.n_redirect] = -1;
	lex->current_pipe = 0;
	lex->current_redirect = 0;
	*num_string = ft_count_total_string(lex, input);
	if (*num_string == 0)
		return (1);
	return (0);
}

char	**ft_tokenize(char *input, t_lexer *lex)
{
	t_temp	temp;
	int		num_string;
	char	**matrix;

	temp.x = 0;
	temp.y = 0;
	if (ft_init_operations(lex, input, &num_string))
		return (NULL);
	matrix = malloc(sizeof(char *) * (num_string + 1));
	while (num_string--)
	{
		while (input[temp.y])
		{
			if (input[temp.y] != 32 && input[temp.y] != '\t')
			{
				matrix[temp.x] = ft_command_split(&input[temp.y], lex, temp.x);
				temp.y += lex->lenght;
				break ;
			}
			temp.y++;
		}
		temp.x++;
	}
	matrix[temp.x] = 0;
	return (matrix);
}

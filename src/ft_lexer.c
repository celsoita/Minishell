/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:45:02 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 17:41:35 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lexer_count_var(char *input, t_lv *lv)
{
	if (lv->variables[lv->nvar] && lv->variables[lv->nvar][0])
	{
		lv->lenght += ft_strlen(lv->variables[lv->nvar]);
		if (input[lv->i] == '?')
			lv->i++;
		else
			while (ft_isalnum(input[lv->i]))
				lv->i++;
	}
	else
	{
		if (lv->i - 1 == 0 || input[lv->i - 2] == ' ' || \
			input[lv->i - 2] == '\t')
		{
			while (ft_isalnum(input[lv->i]))
				lv->i++;
			while (ft_charinstring(input[lv->i], " \t"))
				lv->i++;
		}
		else
			while (ft_isalnum(input[lv->i]))
				lv->i++;
	}
	lv->i--;
	lv->nvar++;
}

bool	ft_lexer_count_op_quote(char *input, t_lv *lv)
{
	if (ft_charinstring(input[lv->i], "|<>") && \
			!lv->in_quote[0] && !lv->in_quote[1])
	{
		if (lv->i == 0)
		{
			while (input[lv->i] == input[lv->i + 1])
			{
				lv->lenght++;
				lv->i++;
			}
			lv->lenght++;
			lv->i++;
		}
		return (1);
	}
	else if (input[lv->i] == '\"' && !lv->in_quote[1])
		lv->in_quote[0] = !lv->in_quote[0];
	else if (input[lv->i] == '\'' && !lv->in_quote[0])
		lv->in_quote[1] = !lv->in_quote[1];
	else if ((input[lv->i] != '\"' && input[lv->i] != '\'') || \
			lv->in_quote[0] || lv->in_quote[1])
		lv->lenght++;
	return (0);
}

void	ft_lexer_count(char *input, t_lexer *lex, t_lv *lv)
{
	while (input[lv->i] && (!ft_charinstring(input[lv->i], " \t") || \
		lv->in_quote[0] || lv->in_quote[1]))
	{
		if (!lv->in_quote[1] && input[lv->i] == '$')
		{
			lv->i++;
			if (input[lv->i] == '?')
				lv->variables[lv->nvar] = ft_expand_exit_status(lex);
			else if (ft_charinstring(input[lv->i], " \t\"$") || \
					input[lv->i] == '\0')
				lv->variables[lv->nvar] = ft_strdup("$");
			else
				lv->variables[lv->nvar] = ft_expander(lex, &input[lv->i]);
			ft_lexer_count_var(input, lv);
		}
		else if (ft_lexer_count_op_quote(input, lv))
			break ;
		if (input[lv->i])
			lv->i++;
	}
	lex->lenght = lv->i;
}

char	*ft_command_split(char *input, t_lexer *lex, int current_pos)
{
	t_lv	lv;

	lv.in_quote[0] = false;
	lv.in_quote[1] = false;
	lv.variables_found = ft_count_variables(input);
	lv.variables = malloc(sizeof(char *) * (lv.variables_found + 1));
	lv.variables[lv.variables_found] = NULL;
	lv.nvar = 0;
	lv.lenght = 0;
	lv.i = 0;
	ft_lexer_count(input, lex, &lv);
	lv.str = malloc(sizeof(char) * lv.lenght + 1);
	lv.nvar = 0;
	lv.in_quote[0] = false;
	lv.in_quote[1] = false;
	lv.lenght = 0;
	lv.i = 0;
	ft_lexer_write(input, lex, &lv, current_pos);
	ft_free_matrix_len(lv.variables, lv.variables_found);
	return (lv.str);
}

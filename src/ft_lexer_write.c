/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:37:46 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 17:41:03 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lexer_write_var_exist(char *input, t_lv *lv)
{
	lv->j = 0;
	while (lv->variables[lv->nvar] && \
		lv->variables[lv->nvar][lv->j])
		lv->str[lv->lenght++] = lv->variables[lv->nvar][lv->j++];
	if (input[lv->i] == '?')
		lv->i++;
	else
		while (ft_isalnum(input[lv->i]))
			lv->i++;
}

void	ft_lexer_write_var_notexist(char *input, t_lv *lv)
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

bool	ft_lexer_write_op_quote(char *input, t_lexer *lex, \
	t_lv *lv, int current_pos)
{
	if (ft_charinstring(input[lv->i], "|<>") && \
		!lv->in_quote[0] && !lv->in_quote[1])
	{
		if (lv->i == 0)
		{
			if (input[lv->i] == '|')
				lex->op.pipe[lex->current_pipe++] = current_pos;
			else
				lex->op.redirect[lex->current_redirect++] = current_pos;
			lv->str[lv->lenght++] = input[lv->i];
			while (input[lv->i] && input[lv->i] == input[lv->i + 1])
				lv->str[lv->lenght++] = input[lv->i++];
		}
		return (1);
	}
	else if (input[lv->i] == '\"' && !lv->in_quote[1])
		lv->in_quote[0] = !lv->in_quote[0];
	else if (input[lv->i] == '\'' && !lv->in_quote[0])
		lv->in_quote[1] = !lv->in_quote[1];
	else if ((input[lv->i] != '\"' && input[lv->i] != '\'') || \
			lv->in_quote[0] || lv->in_quote[1])
		lv->str[lv->lenght++] = input[lv->i];
	return (0);
}

void	ft_lexer_write(char *input, t_lexer *lex, t_lv *lv, int current_pos)
{
	while (input[lv->i] && (!ft_charinstring(input[lv->i], " \t") || \
			lv->in_quote[0] || lv->in_quote[1]))
	{
		if (!lv->in_quote[1] && input[lv->i] == '$')
		{
			lv->i++;
			if (lv->variables[lv->nvar] && lv->variables[lv->nvar][0])
				ft_lexer_write_var_exist(input, lv);
			else
				ft_lexer_write_var_notexist(input, lv);
			lv->i--;
			lv->nvar++;
		}
		else if (ft_lexer_write_op_quote(input, lex, lv, current_pos))
			break ;
		if (input[lv->i])
			lv->i++;
	}
	lv->str[lv->lenght] = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:31:49 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 15:24:58 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_quotes_ops(char *input, int *i, int *ns, bool *br)
{
	if (input[(*i)] == '"')
	{
		(*i)++;
		while (input[(*i)] != '"' && input[(*i)])
			(*i)++;
		if (input[(*i)])
			(*i)++;
	}
	else if (input[(*i)] == '\'')
	{
		(*i)++;
		while (input[(*i)] != '\'' && input[(*i)])
			(*i)++;
		if (input[(*i)])
			(*i)++;
	}
	else if (ft_charinstring(input[(*i)], "|<>"))
	{
		if ((*i) > 0 && !ft_charinstring(input[(*i) - 1], " \t|<>"))
			(*ns)++;
		while (input[(*i)] == input[(*i) + 1])
			(*i)++;
		(*i)++;
		(*br) = 1;
	}
}

void	ft_count_variables_strs(t_lexer *lex, char *input, int *i, int *ns)
{
	char	*temp;

	(*i)++;
	if (ft_charinstring(input[(*i)], " \t\"$") || input[(*i)] == '\0')
	{
		temp = ft_strdup("$");
		if (input[(*i)] == '\0')
			(*ns)++;
	}
	else
		temp = ft_expander(lex, &input[(*i)]);
	if (!temp || !temp[0])
	{
		while (ft_isalnum(input[(*i)]))
			(*i)++;
		while (ft_charinstring(input[(*i)], " \t"))
			(*i)++;
	}
	if (input[(*i)] == '\0')
		(*ns)--;
	free(temp);
}

void	ft_count_next(t_lexer *lex, char *input, int *i, int *ns)
{
	bool	br;

	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '\t')
	{
		if (input[(*i)] == '$' && \
			((*i) == 0 || (input[(*i) - 1] == ' ' || input[(*i) - 1] == '\t')))
			ft_count_variables_strs(lex, input, i, ns);
		else if (ft_charinstring(input[(*i)], "\'\"|<>"))
		{
			br = 0;
			ft_count_quotes_ops(input, i, ns, &br);
			if (br)
				break ;
		}
		else if (input[(*i)] != '\0')
			(*i)++;
	}
}

int	ft_count_total_string(t_lexer *lex, char *input)
{
	int		i;
	int		ns;

	i = 0;
	ns = 0;
	while (input[i] != 0)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i])
			ns++;
		ft_count_next(lex, input, &i, &ns);
	}
	return (ns);
}

int	ft_count_malloc_str(char *input)
{
	int	i;

	i = 0;
	while (input[i] == 32)
		i++;
	if (input[i] == 124)
		return (1);
	while (input[i] != 32 && input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i])
				i++;
			return (i + 1);
		}
		if (input[i] == 32)
			return (i);
		i++;
	}
	return (i);
}

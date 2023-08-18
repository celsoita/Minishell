/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:45:02 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 14:56:57 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_double_quote_control(char *input, char **matrix,int y, int x)
{
	y++;
	if(input[y] !=  '"')
	{
		matrix[x] = ft_substr(input,y-1,ft_count_malloc_str(&input[y - 1]));
	}
	return(matrix[x]);
}

int	ft_count_operators(char *string, char c)
{
	int		i;
	int		ops_found;
	bool	in_quote[2];

	in_quote[0] = false;	// "
	in_quote[1] = false;	// '
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

int	ft_count_variables(char *string)
{
	int		i;
	int		variables_found;
	bool	in_quote[2];

	in_quote[0] = false;	// "
	in_quote[1] = false;	// '
	i = 0;
	variables_found = 0;
	while (string[i] && (string[i] != ' ' || in_quote[0] || in_quote[1]))
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

//questa funzione divide in piu' stringhe  l' input
//quindi prima controlliamo il $ 
//"e""c"h"o ciao "mo'n'd"
//echo echo ciao
//"ec'h'o" ciao => ec'h'o
/*VARIABLES POSSIBILITIES!*/
//echo $PATH					-> /bin/...
//echo $PATH$PATH				-> /bin/.../bin/...
//echo "$PATH"					-> /bin/...
//echo '$PATH'					-> $PATH
//echo "'$PATH'"				-> '/bin/...'
//echo "'"'$PATH'"'"			-> '$PATH'
//echo "$PATH"ciao				-> /bin/...ciao
//echo $PATH(ft_alphanum())		-> 
//echo $PATH(!ft_alphanum())	-> /bin/...(!ft_alphanum())
char	*ft_expand_exit_status(t_lexer *lex)
{
	char *res;
	res = ft_itoa(lex->return_value);
	return (res);
}
char	*ft_command_split(char *input, t_lexer *lex, int current_pos)
{
	int		lenght;
	int		i;
	int		j;
	int		nvar;
	char	*str;
	char	**variables;
	int		variables_found;
	bool	in_quote[2];

	in_quote[0] = false;	// "
	in_quote[1] = false;	// '
	variables_found = ft_count_variables(input);
	// printf("variables_found: %d\t", variables_found);	// REMOVE
	/* COUNT FUNCTION */
	variables = malloc(sizeof(char *) * (variables_found + 1));
	variables[variables_found] = NULL;
	nvar = 0;
	lenght = 0;
	i = 0;
	while (input[i] && (!ft_charinstring(input[i], " \t") || in_quote[0] || in_quote[1]))
	{	// SBAGLIATO[ echo a$USERa a ] GIUSTI[ echo a$USER | echo $USERa a | echo $USERa ]
		if (!in_quote[1] && input[i] == '$')
		{
			i++;
			if (input[i] == '?')
				variables[nvar] = ft_expand_exit_status(lex);
			else
				variables[nvar] = ft_expander(lex, &input[i]);
			if (variables[nvar] && variables[nvar][0])
			{
				lenght += ft_strlen(variables[nvar]);
				if (input[i] == '?')
					i++;
				else
					while (ft_isalnum(input[i]))
						i++;
			}
			else
			{
				if (i - 1 == 0 || input[i - 2] == ' ' || input[i - 2] == '\t')
				{
					while (ft_isalnum(input[i]))
						i++;
					while (ft_charinstring(input[i], " \t"))
						i++;
				}
				else
					while (ft_isalnum(input[i]))
						i++;
			}
			i--;
			nvar++;
		}
		else if (ft_charinstring(input[i], "|<>") && !in_quote[0] && !in_quote[1])
		{
			if (i == 0)
			{
				while (input[i] == input[i + 1])
				{
					lenght++;
					i++;
				}
				lenght++;
				i++;
			}
			break ;
		}
		else if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			lenght++;
		if (input[i])
			i++;
	}
	lex->lenght = i;
	// printf("Lenght: %d\t", lenght);	// REMOVE
	/* WRITE FUNCTION */
	str = malloc(sizeof(char) * lenght + 1);
	nvar = 0;
	in_quote[0] = false;
	in_quote[1] = false;
	lenght = 0;
	i = 0;
	while (input[i] && (!ft_charinstring(input[i], " \t") || in_quote[0] || in_quote[1]))
	{
		if (!in_quote[1] && input[i] == '$')
		{
			i++;
			if (variables[nvar] && variables[nvar][0])
			{
				j = 0;
				while (variables[nvar] && variables[nvar][j])
					str[lenght++] = variables[nvar][j++];
				if (input[i] == '?')
					i++;
				else
					while (ft_isalnum(input[i]))
						i++;
			}
			else
			{
				if (i - 1 == 0 || input[i - 2] == ' ' || input[i - 2] == '\t')
				{
					while (ft_isalnum(input[i]))
						i++;
					while (ft_charinstring(input[i], " \t"))
						i++;
				}
				else
					while (ft_isalnum(input[i]))
						i++;
			}
			i--;
			nvar++;
		}
		else if (ft_charinstring(input[i], "|<>") && !in_quote[0] && !in_quote[1])
		{
			if (i == 0)
			{
				if (input[i] == '|')
					lex->op.pipe[lex->current_pipe++] = current_pos;
				else
					lex->op.redirect[lex->current_redirect++] = current_pos;
				str[lenght++] = input[i];
				while (input[i] && input[i] == input[i + 1])
					str[lenght++] = input[i++];
			}
			break ;
		}
		else if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			str[lenght++] = input[i];
		if (input[i])
			i++;
	}
	str[lenght] = 0;
	ft_free_matrix(variables);
	// printf("DEBUG:\tRECEIVED [%s]\n", str);	// REMOVE

	return (str);
}

// char	*ft_split_tokens(char *input)
// {
// 	int	i;

// 	i = 0;
// }
/*DA FARE LA FUNZIONE PER I ARGOMENTI (DOPO IL COMANDO!)*/
char	**ft_tokenize(char *input, t_lexer *lex)
{
	int	x;
	int	y;
	int	num_string;
	char **matrix;
	// bool	is_command;
	// is_command = true;
	x = 0;
	y = 0;
	lex->op.n_pipe = ft_count_operators(input, '|');
	lex->op.n_redirect = ft_count_operators(input, '>');
	lex->op.n_redirect += ft_count_operators(input, '<');
	lex->op.pipe = malloc(sizeof(int) * (lex->op.n_pipe + 1));
	lex->op.pipe[lex->op.n_pipe] = -1;
	lex->op.redirect = malloc(sizeof(int) * (lex->op.n_redirect + 1));
	lex->op.redirect[lex->op.n_redirect] = -1;
	lex->current_pipe = 0;
	lex->current_redirect = 0;
	num_string = ft_count_total_string(lex, input);	/* TODO: "a$USERa a" DA FARE IN MODO CHE LA PRIMA STRINGA E' STACCATA DALLA SECONDA!*/
	if (num_string == 0)
		return (NULL);
	// printf("Pipes: %d | Redirects: %d | ", lex->op.n_pipe, lex->op.n_redirect);	// REMOVE
	// printf("Strings: %d\n", num_string);	// REMOVE
	matrix = malloc(sizeof(char *) * (num_string + 1));
	while (num_string--)
	{
		while (input[y])
		{
			
			if (input[y] != 32 && input[y] != '\t')
			{
				matrix[x] = ft_command_split(&input[y], lex, x);
				y += lex->lenght;
				break ;
			}
			y++;
		}
		x++;
	}
	matrix[x] = 0;
	return (matrix);
}
/* TODO: QUANDO NON C'E' UN COMANDO DARGLI ERRORE:
	bash: syntax error near unexpected token `>' or `<' or `|'
*/

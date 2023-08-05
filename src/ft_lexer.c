/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:45:02 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/05 19:32:17 by cschiavo         ###   ########.fr       */
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
char	*ft_command_split(char *input, t_lexer *lex)
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
	lenght = 0;
	i = 0;
	variables_found = ft_count_variables(input);
	printf("variables_found: %d\t", variables_found);
	variables = malloc(sizeof(char *) * (variables_found + 1));
	variables[variables_found] = NULL;
	nvar = 0;

	while (input[i] && (input[i] != ' ' || in_quote[0] || in_quote[1]))
	{
		if (!in_quote[1] && input[i] == '$')
		{
			i++;
			variables[nvar] = ft_expander(lex, &input[i]);
			if (variables[nvar] != NULL)
				lenght += ft_strlen(variables[nvar]);
			while (ft_isalnum(input[i]))
				i++;
			i--;
			nvar++;
		}
		else if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			lenght++;
		i++;
	}
	lex->lenght = i;
	str = malloc(sizeof(char) * lenght + 1);
	nvar = 0;
	in_quote[0] = false;
	in_quote[1] = false;
	lenght = 0;
	i = 0;
	while (input[i] && (input[i] != ' ' || in_quote[0] || in_quote[1]))
	{
		if (!in_quote[1] && input[i] == '$')
		{
			j = 0;
			while (variables[nvar] && variables[nvar][j])
				str[lenght++] = variables[nvar][j++];
			i++;
			while (ft_isalnum(input[i]))
				i++;
			i--;
			nvar++;
		}
		else if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			str[lenght++] = input[i];
		i++;
	}
	str[lenght] = 0;
	ft_free_matrix(variables);
	printf("DEBUG:\tRECEIVED [%s]\n", str);

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
	num_string = ft_count_total_string(input, 32);
	matrix = malloc(sizeof(char *) * (num_string + 1));
	while (num_string--)
	{
		while (input[y])
		{
			
			if (input[y] != 32)
			{
				matrix[x] = ft_command_split(&input[y], lex);
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

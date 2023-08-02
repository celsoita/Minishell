/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:45:02 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/02 19:19:22 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_double_quote_control(char *input, char **matrix,int y, int x)
{
	y++;
	if(input[y] !=  '"')
	{
		matrix[x] = ft_substr(input,y-1,ft_count_malloc_str(&input[y - 1]));
	}
	return(matrix[x]);
}

//questa funzione divide in piu' stringhe  l' input
//quindi prima controlliamo il $ 
//"e""c"h"o ciao "mo'n'd"
//echo echo ciao
//"ec'h'o" ciao => ec'h'o
char	*ft_command_split(char *input, t_lexer *lex)
{
	int		lenght;
	int		i;
	char	*str;
	bool	in_quote[2];

	in_quote[0] = false;	// "
	in_quote[1] = false;	// '
	lenght = 0;
	i = 0;
	while (input[i] && (input[i] != ' ' || in_quote[0] || in_quote[1]))
	{
		if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			lenght++;
		i++;
	}
	lex->lenght = i;
	str = malloc(sizeof(char) * lenght + 1);
	in_quote[0] = false;
	in_quote[1] = false;
	lenght = 0;
	i = 0;
	while (input[i] && (input[i] != ' ' || in_quote[0] || in_quote[1]))
	{
		if (input[i] == '\"' && !in_quote[1])
			in_quote[0] = !in_quote[0];
		else if (input[i] == '\'' && !in_quote[0])
			in_quote[1] = !in_quote[1];
		else if ((input[i] != '\"' && input[i] != '\'') || in_quote[0] || in_quote[1])
			str[lenght++] = input[i];
		i++;
	}
	str[lenght] = 0;
	printf("DEBUG:\tRECEIVED [%s]\n", str);

	return (str);
}

/*DA FARE LA FUNZIONE PER I ARGOMENTI (DOPO IL COMANDO!)*/
char	**ft_tokenize(char *input)
{
	int	x;
	int	y;
	int	num_string;
	char **matrix;
	bool	is_comand;
	t_lexer	lex;
	is_comand = true;
	x = 0;
	y = 0;
	num_string = ft_count_total_string(input, 32);
	matrix = malloc((num_string + 1) * sizeof(char *));
	while (num_string--)
	{
		while (input[y])
		{
			
			if (input[y] != 32)
			{
				if (is_comand)
				{
					matrix[x] = ft_command_split(input, &lex) ;
					y += lex.lenght;
					is_comand = false;
					break ;
				}
				else
				{
					matrix[x] = ft_substr(input, y, ft_count_malloc_str(&input[y]));
					y += ft_count_malloc_str(&input[y]);
					break ;
				}
			}
			y++;
		}
		x++;
	}
	matrix[x] = 0;
	return (matrix);
}

/*
	serve una funzione per splittare i path e metterli in una
	 matrix , poi dopo successivamente bisogna aggiungere il path con il comando e testare
	 con access se il comando esiste e poi in futuro passare tutto a execve

*/
char	**ft_path_splitter()
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	return(paths);
}
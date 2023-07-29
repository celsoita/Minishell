/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/29 16:39:43 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
	serve una funzione per creare i token/ dividere una stringa in piu'
	stringhe, stringa-comando, stringhe successive.

*/




//str di es :   echo -n  "ciao mondo"|" banana" 
int	ft_count_total_string(char *input, char c)
{
	int	i;
	int	ns;

	i = 0;
	ns = 0;
	while (input[i] != 0)
	{
		if (input[i] != c)
		{
			ns++;
			while (input[i] != c && input[i] != '\0')
				i++;
		}
		if (input[i] != '\0')
			i++;
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
		if (input[i] == 32)
			return (i);
		i++;
	}
	return (i);	
}
//echo -n ciao mondo| banana
char	**ft_tokenize(char *input)
{
	int	x;
	int	y;
	int	num_string;
	char **matrix;

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
				matrix[x] = ft_substr(input, y, ft_count_malloc_str(&input[y]));
				y += ft_count_malloc_str(&input[y]);
				break ;
			}
			y++;
		}
	x++;
	}
	matrix[x] = 0;
	return (matrix);
}
/*
	serve una funzione che controlla la matrice precedentemente creata 
	e passa a execve tutto tranne | e >> <<  > < 
*/


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

int main(int argc, char **argv, char **env)
{
	char *input;
	t_lexer	lex;
	env =0;
	input = argv[1];
	argc = 0;
	lex.paths = ft_path_splitter();
	while (1)
	{
		ft_create_prompt_username();
		input = readline("");
		lex.tokens = ft_tokenize(input);
		if (!strcmp(input, "exit"))
		{
			free(input);
			return (1);
		}
		if (input[0])
			add_history(input);
		
	}
	return (0);
}
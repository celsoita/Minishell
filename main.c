/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/30 12:23:35 by cschiavo         ###   ########.fr       */
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
			if (input[i] == '"')
			{
				i++;
				while(input[i] != '"')
					i++;	
				ns++;
			}
			else
			{
				ns++;
				while (input[i] != c && input[i] != '\0')
					i++;
			}
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
		if (input[i] == '"')
		{
			i++;
			while(input[i] != '"')
				i++;
			return(i);
		}
		if (input[i] == 32)
			return (i);
		i++;
	}
	return (i);	
}
/*
	DA CONTROLLARE IL  CAVOLO DI COSO QUA CHE NON PRENDE LE " COME UNICO ARGOMENTO"
	ORA SONO STANCO VEDO DOMANI COMUNQUE RICORDATI CHE ORA STA SALVANDO QUALCOSA A META
	DOMANI PARTI DAL GDB
*/
char	*ft_double_quote_control(char *input, char **matrix,int y, int x)
{
	y++;
	if(input[y] !=  '"')
	{
		matrix[x] = ft_substr(input,y-1,ft_count_malloc_str(&input[y - 1]));
	}
	return(matrix[x]);
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
				if (input[y] == '"')
				{
					matrix[x] = ft_double_quote_control(input,matrix,y,x);
					y += ft_count_malloc_str(&input[y]);
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

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	
	while(s1[i])
	{
		res[i] =s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while(s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return(res);
}

void	ft_try_path(t_lexer lex, char **env)
{
	char *path_try;
	int	i;

	i = 0;
	while(1)
	{
		path_try = ft_strjoin_path(lex.paths[i],lex.tokens[0]);
		if (!access(path_try, F_OK))
		{
			execve(path_try, lex.tokens, env);
		}
		else
			i++;
	}
}
int main(int argc, char **argv, char **env)
{
	char *input;
	t_lexer	lex;
	
	(void)argc;
	env =0;
	input = argv[1];
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
		ft_try_path(lex,env);
		if (input[0])
			add_history(input);
		
	}
	return (0);
}
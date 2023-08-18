/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:26:24 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 15:02:54 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env, bool exp)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	i = ft_strlen_matrix(env);
	while(y < i)
	{
		if (exp)
			printf("declare -x ");
		x = 0;
		while (env[y][x])
		{
			printf("%c",env[y][x]);
			if (exp && env[y][x] == '=')
				printf("\"");
			x++;
		}
		if (exp)
			printf("\"");
		printf("\n");
		y++;
	}
}
//str di es :   echo -n  "ciao mondo"|" banana" 
// questa funzione conta il numero totale  di stringhe
int	ft_count_total_string(t_lexer *lex, char *input)
{
	char	*temp;
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
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '$' && (i == 0 || (input[i - 1] == ' ' || input[i - 1] == '\t')))
			{
				i++;
				temp = ft_expander(lex, &input[i]);
				if (!temp || !temp[0])
				{
					while (ft_isalnum(input[i]))
						i++;
					while (ft_charinstring(input[i], " \t"))
						i++;
				}
				if (!input[i])
					ns--;
				free(temp);
			}
			else if (input[i] == '"')
			{
				i++;
				while(input[i] != '"' && input[i])
					i++;
				if (input[i])
					i++;
			}
			else if (input[i] == '\'')
			{
				i++;
				while(input[i] != '\'' && input[i])
					i++;
				if (input[i])
					i++;
			}
			else if (ft_charinstring(input[i], "|<>"))
			{
				if (i > 0 && !ft_charinstring(input[i - 1], " \t|<>"))
					ns++;
				while (input[i] == input[i + 1])
					i++;
				i++;	// ||ciao||
				break ;
			}
			else if (input[i] != '\0')
				i++;
		}
	}
	return (ns);

}
//questa funzione serve a contare il numero necessario per malloccare la uso nella mia split modificata
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
			while(input[i] != '"' && input[i])
				i++;
			return(i+1);
		}
		if (input[i] == 32)
			return (i);
		i++;
	}
	return (i);	
}
char **ft_path_splitter(t_lexer *lex)
{
	char *path;
	char **res;
	
	path = ft_expander(lex, "PATH");
	res = ft_split(path, ':');
	free(path);
	return (res);
}

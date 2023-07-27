/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:32 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/27 18:38:28 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo
//ciao | ls come mondo
//|
//wc

//cat
//-e
//ciao
//mondo

//ls -la
//ciao mondo ls -l
//ls -l
//guardo

//Da creare / built in 
/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

//echo $HOME  "'ciao come va'"
void	ft_echo(char **str)
{
	int	x;
	int	y;
	char *res;
	int join_next;
	int	n;

	x = 0;
	y = 0;
	n = 0;
	join_next = 0;
	int len = ft_strlen_matrix(str);
	while(y < len)
	{
		// if (join_next == len)
		// 		join_next -1;
		if (!strcmp (str[y],"echo"))
			y++;
		if (!strcmp (str[y],"-n"))
		{
			n  = 1;
			y++;
		}
		//echo -n ciao mondo banana
		if(len >= 3)
		{
			join_next = y + 1;
			res = ft_strjoin(str[y], str[join_next]);
			if (join_next == len)
				break ;
			y++;
		}
		else
			res = str[y];
		y++;
	}
	if (n)
		printf("%s", res);
	else
		printf("%s\n", res);	
}
char **ft_analize_input(char *input)
{
	char **res;
	
	res = ft_split(input,' ');

	return (res);
}
int main (int argc, char **argv, char **env)
{
	argc = 0;
	
	char *input;
   	char res[1024];
	// char **clean_input;
	int	size;
	int count_input;
	
	count_input = 0;
	input = argv[1];
	while(1)
	{
		ft_create_prompt_username();
		input = readline("");
		// clean_input  = ft_analize_input(input);
		// printf("matrix%d\n",ft_strlen_matrix(clean_input));
		//printf("input:%s\n =",input);
		size = 0;
		while(input[size])
		{
			printf("count:%d\n",ft_count_input(&input[size]));
			count_input = ft_count_input(&input[size]);
			
			size = size + count_input;
		}
		if (!strcmp(input, "exit"))
		{
			free(input);
			break ;
		}
		if (!strcmp(input,"pwd"))
		{
			if (getcwd(res, sizeof(res)) != NULL)
				printf("%s\n", res);
			free(input);
		}
		if (!strcmp(input,"env"))
		{
			ft_print_env(env);
			free(input);
		}
		if (!strcmp(input, "clear"))
		{
			ft_clear_screen();
			free(input);
		}
		// if (!strcmp(clean_input[0], "echo"))
		// {
		// 	ft_echo(clean_input);
		// 	free(input);
		// }
		if (input[0])
			add_history(input);
	}
	return (0);
}

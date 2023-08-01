/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:32 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/01 19:31:06 by cschiavo         ###   ########.fr       */
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
/*
questa funzione deve splittare il path per darmi i path
 da testare all'interno di acces
 che poi andranno passatti al execve
*/
char **ft_path_splitter(void)
{
	char *path;
	char **res;

	path = getenv("PATH");
	res = ft_split(path, ':');
	return (res);
}

// void	ft_exec_exec_path(char *path, char **flag,char **env)
// {
// 	if (!access(path,F_OK))
// 	{
// 		execve(path, flag, env);
// 	}
// 	else
// 		printf("ciao");
// }
bool	ft_action_terminal(char *input, char **env,char *res)
{
	
	ft_create_prompt_username();
		input = readline("");
		if (!strcmp(input, "exit"))
		{
			free(input);
			return (1);
		}
		if (!strcmp(input,"pwd"))
		{
			if (getcwd(res, sizeof(res)) != NULL)
			{
				printf("%s\n", res);
			}
			free(input);
		}
		if (!strcmp(input,"env"))
		{
			ft_print_env(env);
			free(input);
		}
		if (!strcmp(input,"env"))
		{
			ft_print_env();
			free(input);
		}
		// if (!strcmp(input, "ls"))
		// {
		// 	ft_exec_exec_path(path,flag,env);
		// }
		if (input[0])
			add_history(input);
	return(0);
}
int main (int argc, char **argv, char **env)
{
	argc = 0;
	
	char *input;
   	char res[1024];
	input = argv[1];
	char **path_try;
	
	path_try = ft_path_splitter();
	while(1)
	{
		if (ft_action_terminal(input, env, res))
			break ;
	}
	return (0);
}

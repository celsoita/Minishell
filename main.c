/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/02 19:06:39 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	serve una funzione che controlla la matrice precedentemente creata 
	e passa a execve tutto tranne | e >> <<  > < 
*/


void	ft_free_matrix(char **matrix)
{
	int	i;

	i = ft_strlen_matrix(matrix);
	while(i--)
	{
		free(matrix[i]);
	}
	free(matrix);
}
bool	ft_check_is_variable(char	*token)
{
	int	x;

	x = 0;
	while(token[x])
	{
		if(token[x] == '$')
			return(0);
		if(token[x] == '=' && token[x + 1] != 32)
			return (1);
		x++;
	}
	return (0);
}

int	ft_check_builtin(t_lexer *lex)
{
	if (!strcmp(lex->clean_comand, "export") || !strcmp(lex->tokens[0], "export"))
		return (1);
	if (!strcmp(lex->clean_comand, "env2") || !strcmp(lex->tokens[0], "env2"))
		return (2);
	return(0);
	/*echo with option -n
◦ $cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit w*/
}
//$cavolo=figlio

// int	ft_search_str_in_matrix(char **env,char *str)
// {
// 	int	y;
// 	int	lenght_matrix;
// 	lenght_matrix = ft_strlen_matrix(env);
// 	y = 0;
// 	while(y < lenght_matrix)
// 	{

// 	}


// }
// char **ft_unset(char **env)
// {

// }
int main(int argc, char **argv, char **env)
{
	char *input;
	t_lexer	lex;
	int	flag_input;
	(void)argc;
	input = argv[1];
	lex.paths = ft_path_splitter();
	signal(SIGINT,sigint_handler);
	flag_input = 0;
	lex.env_copy = ft_copy_env(env);
	while (1)
	{
		input = readline(ft_create_prompt_username());
		lex.tokens = ft_tokenize(input);
		// ft_command_split(input);
		if(ft_check_command(&lex) == 0 || ft_check_command(&lex) == 1)
		{
			if (ft_check_builtin(&lex))
			{
				flag_input = ft_check_builtin(&lex);
				if (flag_input == 1)
					lex.env_copy = ft_dup_matrix(lex.env_copy,&lex);
				if (flag_input == 2)
				{
					ft_print_env(lex.env_copy);
					// free(input);
				}
			}
			// if (ft_path_try(&lex) == 1)
			// {
			// 	flag_input = 1;
			// 	ft_exec_path(&lex,env,flag_input); 	
			// }
			// else if (ft_path_try(&lex) == 0)
			// {
			// 	ft_exec_path(&lex,env,flag_input);
			// }
			if(!strcmp(input, "exit"))
			{
				free(input);
				return (1);
			}			
			if (input[0])
				add_history(input);
		}
		else
			return(ft_perror("ops ho sbagliato"));
		free(input);
	}
	return (0);
}
/*
	devi mettere unset della variabile exportata e fare altri controlli al momento sembra che ;'export funzioni

*/

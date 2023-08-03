/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/03 17:21:47 by cschiavo         ###   ########.fr       */
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
	lex->flags = 0;
	if (!strcmp(lex->tokens[0], "echo"))
		lex->flags = 1;
	if (!strcmp(lex->tokens[0], "cd"))
		lex->flags = 2;
	if (!strcmp(lex->tokens[0], "pwd"))
		lex->flags = 3;
	if (!strcmp(lex->tokens[0], "export"))
		lex->flags = 4;
	if (!strcmp(lex->tokens[0], "unset"))
		lex->flags = 5;
	if (!strcmp(lex->tokens[0], "env"))
		lex->flags = 6;
	if (!strcmp(lex->tokens[0], "exit"))
		lex->flags = 7;
	return (lex->flags);
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
bool	ft_check_syntax_error(t_lexer *lex)
{
	int	i;

	i = 0;
	while(lex->tokens[0][i])
	{
		if (lex->tokens[0][i] == '\'' || lex->tokens[0][i] == '"')
			return (0);
		i++;
	}
	return (1);
}
bool	ft_check_is_executable(t_lexer *lex)
{
	int	i;
	char	*path_try;
	
	i = 0;
	
	while (lex->paths[i])
	{
		path_try = ft_strjoin_path(lex->paths[i], lex->tokens[0]);
		if (!access(path_try, F_OK))
		{
			free(path_try);
			return (1);
		}
		i++;
		free(path_try);
	}
	return (0);
}
int	ft_exec_builtin(t_lexer *lex)
{
	int	return_value;

	return_value = 0;
	//echo
	if (lex->flags == 1)
		printf("echo\n");
	//cd
	if (lex->flags == 2)
		printf("cd\n");
	//pwd
	if (lex->flags == 3)
		printf("pwd\n");
	//export
	if (lex->flags == 4)
		lex->env_copy = ft_dup_matrix(lex->env_copy,lex);
	//unset
	if (lex->flags == 5)
		printf("unset\n");
	//env
	if (lex->flags == 6)
		ft_print_env(lex->env_copy);
	//exit
	if (lex->flags == 7)
	{
		return_value = printf("exit\n");
		ft_free_matrix(lex->tokens);
		ft_free_matrix(lex->paths);
		ft_free_matrix(lex->env_copy);
	}
	return (return_value);
}
int main(int argc, char **argv, char **env)
{
	char *input;
	char	*prompt;
	t_lexer	lex;
	int	flag_input;
	(void)argc;
	input = argv[1];
	lex.paths = ft_path_splitter();
	signal(SIGINT,sigint_handler);
	flag_input = 0;
	lex.env_copy = ft_copy_env(env);
	lex.is_builtin = false;
	while (1)
	{
		prompt = ft_create_prompt_username();
		input = readline(prompt);
		free(prompt);
		lex.tokens = ft_tokenize(input);
		// ft_command_split(input);
		if (ft_check_builtin(&lex))
			lex.is_builtin = true;
		else
			lex.is_builtin = false;
		if (lex.is_builtin)
		{
			if (ft_exec_builtin(&lex))
			{
				free(input);
				return (1);
			}
		}
		else if(ft_check_is_executable(&lex) && ft_check_syntax_error(&lex))
			ft_exec_path(&lex); 	
		else
			printf("%s: not a command\n", lex.tokens[0]);
		if (input[0])
			add_history(input);
		free(input);
		ft_free_matrix(lex.tokens);
	}
	return (0);
}
/*
	devi mettere unset della variabile exportata e fare altri controlli al momento sembra che ;'export funzioni

*/

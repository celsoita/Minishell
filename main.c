/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/01 19:31:08 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	serve una funzione che controlla la matrice precedentemente creata 
	e passa a execve tutto tranne | e >> <<  > < 
*/

/*
	devo fare la copia di env, quindi devo scorrere la matrice e copiare 
	tutto in una nuova matrice/qalcosa che posso usare poi;
	ma ha senso copiare env? se hai quello li modificabile mmh

*/



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
/*
dovrei fare una funzione di pulizia input dove ad esempio 'e'c'h'o tolgo  le single quote,
vedo se esiste nelle mie built in con una funzione ....se la non ci sta 
provo con access se esiste se esiste la mando in un processo fork con un altra funzione 
dove esegue tutto, altrimenti perror "qualcosa" 
*/

char	**ft_dup_matrix(char **env, t_lexer *lex)
{
	int	num_string;
	int	x;
	int	len_env;
	char	**matrix_env;
	int	i;
	int	y;
	int	dimension_token;
	int	count;
	matrix_env = 0;
	y = 1;
	 dimension_token = ft_strlen_matrix(lex->tokens);
	count = 0;
	while(y < dimension_token)
	{
		if (ft_check_is_variable(lex->tokens[y]) == 1)
			count++;
		y++;
	}
	y = 1;
	while(y < dimension_token)
	{
		if (ft_check_is_variable(lex->tokens[y]) == 1)
		{
			num_string = 0;
			len_env = 0;
			num_string = ft_strlen_matrix(env);
			matrix_env = malloc (sizeof(char *) * (num_string + count));
			i = 0;
			x = 0;
			while(i < num_string + count)
			{
				if (i >= num_string)
				{
					x = 0;
					len_env = ft_strlen(lex->tokens[y]);
					matrix_env[i] = malloc(sizeof(char *) * len_env + 1);
					while(x < len_env)
					{
						matrix_env[i][x] = lex->tokens[y][x];
						x++;
					}
					y++;
					matrix_env[i][x] = '\0';
				}
				else
				{

					len_env = ft_strlen(env[i]);
					matrix_env[i] = malloc(sizeof(char *) * ft_strlen(env[i]) + 1);
					
					while(x < len_env)
					{
						matrix_env[i][x] = env[i][x];
						x++;
					}
					matrix_env[i][x] = '\0';
					x = 0;
				}
				i++;
			}
		}
		y++;
	}
	return (matrix_env);
}
bool	ft_check_builtin(t_lexer *lex)
{
	if (!strcmp(lex->clean_comand, "export") || !strcmp(lex->tokens[0], "export"))
		return (1);
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
	while (1)
	{
		ft_create_prompt_username();
		input = readline("");
		lex.tokens = ft_tokenize(input);
		if(ft_check_command(&lex) == 0 || ft_check_command(&lex) == 1)
		{
			if (ft_check_builtin(&lex) == 1)
			{
				lex.new_env = ft_dup_matrix(env,&lex);
			}
			if (!strcmp(input,"env2"))
			{
				ft_print_env(lex.new_env);
				free(input);
			}

			if (ft_path_try(&lex) == 1)
			{
				flag_input = 1;
				ft_exec_path(&lex,env,flag_input); 	
			}
			else if (ft_path_try(&lex) == 0)
			{
				ft_exec_path(&lex,env,flag_input);
			}
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/05 19:31:47 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_builtin(t_lexer *lex)
{
	int	return_value;

	return_value = 0;
	//echo
	if (lex->flags == 1)
		ft_echo(lex);
	//cd
	if (lex->flags == 2)
		ft_chdir(lex);
	//pwd
	if (lex->flags == 3)
		printf("%s\n", lex->cwd);
	//export
	if (lex->flags == 4)
		ft_export(lex->env_copy, lex);
	//unset
	if (lex->flags == 5)
		lex->env_copy = ft_unset(lex);
	//env
	if (lex->flags == 6)
		ft_print_env(lex->env_copy, false);
	//exit
	if (lex->flags == 7)
		return_value += printf("exit\n");
	return (return_value);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_lexer	lex;

	(void)argc;
	signal(SIGINT,sigint_handler);
	signal(SIGQUIT,SIG_IGN);
	lex.env_copy = ft_copy_env(env);
	lex.paths = ft_path_splitter(&lex);
	lex.is_builtin = false;
	lex.cwd = getcwd(NULL, 0);
	while (1)
	{
		prompt = ft_create_prompt_username(&lex, argv[1]);
		input = NULL;
		while (!input || input[0] == '\0')
		{
			free(input);
			input = readline(prompt);
			if (!input)
			{
				printf("\n");
				free(prompt);
				free(input);
				free(lex.cwd);
				ft_free_matrix(lex.paths);
				ft_free_matrix(lex.env_copy);
				return (1);
			}
		}
		free(prompt);
		lex.tokens = ft_tokenize(input, &lex);
		// ft_token_expander(&lex);
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
				free(lex.cwd);
				ft_free_matrix(lex.tokens);
				ft_free_matrix(lex.paths);
				ft_free_matrix(lex.env_copy);
				return (1);
			}
		}
		else if(ft_check_is_executable(&lex) && ft_check_syntax_error(&lex))
			ft_exec_path(&lex); 	
		else
			printf("%s: not a command\n", lex.tokens[0]);
		if (input[0])
			add_history(input);
		ft_free_matrix(lex.tokens);
	}
	return (0);
}
/*
	quando si exporta una variabile con lo stesso nome bisogna unsettarla e riscrivere
	task per domani sistemare questa cosa, controllare meglio gli altri comandi, e iniziare a capire i fork

*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 16:42:07 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_empty_redirections(t_lexer *lex)
{
	char	*arg;

	lex->current_redirect = 0;
	while (lex->current_redirect < lex->op.n_redirect)
	{
		arg = lex->tokens[lex->op.redirect[lex->current_redirect] + 1];
		if (!arg || arg[0] == '|' || arg[0] == '>' || arg[0] == '<')
		{
			ft_perror("bash: syntax error near unexpected token `%s'\n", \
				lex->tokens[lex->op.redirect[lex->current_redirect]]);
			return (1);
		}
		lex->current_redirect++;
	}
	lex->current_redirect = 0;
	return (0);
}

/*
	lex->flags:
	1:	echo
	2:	cd
	3:	pwd
	4:	export
	5:	unset
	6:	env
	7:	exit
*/
int	ft_exec_builtin(t_lexer *lex)
{
	lex->can_return = false;
	if (lex->flags == 1)
		ft_echo(lex);
	if (lex->flags == 2)
		ft_chdir(lex);
	if (lex->flags == 3)
		printf("%s\n", lex->cwd);
	if (lex->flags == 4)
		ft_export(lex);
	if (lex->flags == 5)
		ft_unset(lex, false);
	if (lex->flags == 6)
		ft_print_env(lex->env_copy, false);
	if (lex->flags == 7)
		ft_exit(lex);
	return (lex->return_value);
}

void	ft_execute(t_lexer *lex)
{
	lex->global_tokens = lex->tokens;
	if (lex->op.n_pipe > 0)
	{
		if (!ft_init_pipe(lex))
			return ;
	}
	else
	{
		lex->args = ft_tokens_args(lex);
		if (lex->op.n_redirect > 0)
			ft_redirects(lex);
	}
	// {// ft_print_tokens
	// 	if (lex->tokens)
	// 		{
	// 			ft_perror("\n----------TOKENS---------\n");
	// 			int len;
	// 			int	j;
	// 			char	*line;
	// 			j = 0;
	// 			len = ft_strlen_matrix(lex->tokens);
	// 			while (j < len)
	// 			{
	// 				line = ft_strjoin(lex->tokens[j], "\n");
	// 				ft_perror(line, 0);
	// 				free(line);
	// 				j++;
	// 			}
	// 			ft_perror("--------------------------\n\n");
	// 		}
	// 	}// END ft_print_arguments
	// {// ft_print_arguments
	// 	if (lex->args)
	// 	{
	// 		ft_perror("\n--------ARGOMENTI---------\n");
	// 		int len;
	// 		int	j;
	// 		char	*line;
	// 		j = 0;
	// 		len = ft_strlen_matrix(lex->args);
	// 		while (j < len)
	// 		{
	// 			line = ft_strjoin(lex->args[j], "\n");
	// 			ft_perror(line, 0);
	// 			free(line);
	// 			j++;
	// 		}
	// 		ft_perror("--------------------------\n\n");
	// 	}
	// 	}// END ft_print_arguments
	if (lex->args && lex->args[0])
	{
		if (ft_check_builtin(lex))
		{
			lex->return_value = ft_exec_builtin(lex);
			if (lex->can_return == true)
			{
				lex->tokens = lex->global_tokens;
				return ;
			}
		}
		else if (ft_check_is_executable(lex) && ft_check_syntax_error(lex))
			ft_exec_path(lex);
		else if (lex->paths && ft_strchr(lex->args[0], '/'))
		{
			if (!access(lex->args[0], F_OK) && access(lex->args[0], X_OK))
			{
				ft_perror("%s: Permission denied\n", lex->args[0]);
				lex->return_value = 126;
			}
			else
			{
				ft_perror("%s: No such file or directory\n", lex->args[0]);
				lex->return_value = 127;
			}
		}
		else if (lex->paths && lex->args[0] != NULL)
		{
			ft_perror("%s: not a command\n", lex->args[0]);
			lex->return_value = 127;
		}
	}
	else
	{
		ft_perror("bash: Missing command\n");
		lex->return_value = 1;
	}
	ft_free_matrix(lex->args);
	if (lex->is_executing)
	{
		ft_free((void **)&lex->cwd);
		ft_free((void **)&lex->op.pipe);
		ft_free((void **)&lex->op.redirect);
		lex->tokens = lex->global_tokens;
		ft_free_matrix(lex->tokens);
		ft_free_matrix(lex->paths);
		ft_free_matrix(lex->env_copy);
		// ft_perror("EXIT STATUS(%d)\n", lex->return_value);	// REMOVE
		exit (lex->return_value);
	}
	if (lex->stds.stdin != STDIN_FILENO)
		dup2(lex->stds.stdin, STDIN_FILENO);
	if (!access(".temp", F_OK))
	{
		if (!fork())
		{
			lex->args = malloc(sizeof(char *) * (2 + 1));
			lex->args[0] = "/usr/bin/rm";
			lex->args[1] = ".temp";
			lex->args[2] = NULL;
			execve("/usr/bin/rm", lex->args, lex->env_copy);
			ft_free((void **)&lex->cwd);
			ft_free((void **)&lex->op.pipe);
			ft_free((void **)&lex->op.redirect);
			lex->tokens = lex->global_tokens;
			ft_free_matrix(lex->tokens);
			ft_free_matrix(lex->args);
			ft_free_matrix(lex->paths);
			ft_free_matrix(lex->env_copy);
			exit (lex->return_value);
		}
		waitpid(-1, NULL, 0);
	}
	dup2(lex->stds.stdin, STDIN_FILENO);
	dup2(lex->stds.stdout, STDOUT_FILENO);
}

char	*ft_input(char *prompt)
{
	char	*input;

	input = NULL;
	while (!input || input[0] == '\0')
	{
		free(input);
		input = readline(prompt);
		if (!input)
		{
			printf("\n");
			free(prompt);
			return (input);
		}
	}
	free(prompt);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_lexer	lex;

	(void)argc;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	lex.stds.stdin = dup(STDIN_FILENO);
	lex.stds.stdout = dup(STDOUT_FILENO);
	lex.env_copy = ft_copy_env(env);
	lex.paths = ft_path_splitter(&lex);
	lex.absolute_path = false;
	lex.cwd = getcwd(NULL, 0);
	lex.pipe_num = 0;
	lex.return_value = 0;
	lex.op.pipe = NULL;
	lex.op.redirect = NULL;
	while (1)
	{
		input = ft_input(ft_create_prompt(&lex, argv[1]));
		if (!input)
			break ;
		lex.tokens = ft_tokenize(input, &lex);
		if (!ft_empty_redirections(&lex))
		{
			lex.current_pipe = 0;
			lex.lenght = 0;
			lex.is_executing = false;
			lex.can_return = false;
			ft_execute(&lex);
			if (lex.can_return == true)
			{
				ft_free_matrix(lex.tokens);
				ft_free_matrix(lex.args);
				break ;
			}
		}
		if (input[0])
			add_history(input);
		ft_free_matrix(lex.tokens);
		ft_free((void **)&lex.op.pipe);
		ft_free((void **)&lex.op.redirect);
	}
	free(input);
	ft_free((void **)&lex.op.pipe);
	ft_free((void **)&lex.op.redirect);
	ft_free((void **)&lex.cwd);
	ft_free_matrix(lex.paths);
	ft_free_matrix(lex.env_copy);
	return (lex.return_value);
}

/*
	TODO:
		TESTS:
				NO ERRORS!
*/

// clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

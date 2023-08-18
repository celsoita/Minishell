/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 14:53:01 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_builtin(t_lexer *lex)
{
	lex->can_return = false;
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
		ft_export(lex);
	//unset
	if (lex->flags == 5)
		ft_unset(lex, false);
	//env
	if (lex->flags == 6)
		ft_print_env(lex->env_copy, false);
	//exit
	if (lex->flags == 7)
	{
		lex->can_return = true;
		if (lex->args[1])
		{
			if (lex->args[2])
			{
				printf("bash: exit: too many argument\n");
				lex->can_return = false;
				lex->return_value = 1;
			}
			else
				lex->return_value = ft_atoi(lex->args[1]) % 256;
		}
		printf("exit\n");
	}
	return (lex->return_value);
}

int	ft_init_pipe(t_lexer *lex)
{
	pid_t pid;

	pid = 0;
	lex->is_executing = true;
	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &lex->return_value, 0);
		lex->is_executing = false;
		ft_free((void **)&lex->op.pipe);
		ft_free((void **)&lex->op.redirect);
		return (0);	// FATHER
	}
	lex->lenght = 0;
	if (ft_pipe(lex, lex->tokens, 0, 0) != -1)
	{
		waitpid(pid, &lex->return_value, 0);
		ft_free((void **)&lex->cwd);
		ft_free((void **)&lex->op.pipe);
		ft_free((void **)&lex->op.redirect);
		lex->tokens = lex->global_tokens;
		ft_free_matrix(lex->tokens);
		ft_free_matrix(lex->paths);
		ft_free_matrix(lex->env_copy);
		exit (0);
	}
	lex->args = ft_matrix_shell(lex);
	return (1);		// CHILD
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
		lex->args = ft_matrix_shell(lex);
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
	if (lex->args)
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
		else if(ft_check_is_executable(lex) && ft_check_syntax_error(lex))
			ft_exec_path(lex);
		else if (lex->args[0] != NULL)
		{
			printf("%s: not a command\n", lex->args[0]);
			lex->return_value = 127;
		}
	}
	else
	{
		printf("bash: Missing command\n");
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
		exit (0);
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
			exit (0);
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

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_lexer	lex;

	(void)argc;
	signal(SIGINT,sigint_handler);
	signal(SIGQUIT,SIG_IGN);
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
		input = ft_input(ft_create_prompt_username(&lex, argv[1]));
		if (!input)
			break ;
		lex.tokens = ft_tokenize(input, &lex);
		lex.current_pipe = 0;
		lex.current_redirect = 0;
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
		if (input[0])
			add_history(input);
		ft_free_matrix(lex.tokens);
		if (lex.op.pipe)
			ft_free((void **)&lex.op.pipe);
		if (lex.op.redirect)
			ft_free((void **)&lex.op.redirect);
	}
	free(input);
	if (lex.op.pipe)
		ft_free((void **)&lex.op.pipe);
	if (lex.op.redirect)
		ft_free((void **)&lex.op.redirect);
	ft_free((void **)&lex.cwd);
	ft_free_matrix(lex.paths);
	ft_free_matrix(lex.env_copy);
	return (lex.return_value);
}

/*
	TODO:
		TESTS: echo $PATH|tr ":" " "| cat > ciao
*/

// clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

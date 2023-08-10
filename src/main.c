/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/10 19:14:24 by cschiavo         ###   ########.fr       */
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
		if (lex->tokens[1])
		{
			if (lex->tokens[2])
			{
				printf("bash: exit: too many argument\n");
				lex->can_return = false;
				lex->return_value = 1;
			}
			else
				lex->return_value = ft_atoi(lex->tokens[1]) % 256;
		}
		printf("exit\n");
	}
	return (lex->return_value);
}

int	ft_init_pipe(t_lexer *lex)
{
	pid_t pid;

	pid = 0;
	if (!lex->is_executing)
	{
		lex->is_executing = true;
		pid = fork();
	}
	if (pid != 0)
	{
		waitpid(pid, &lex->return_value, 0);
		lex->is_executing = false;
		free(lex->op.pipe);
		free(lex->op.redirect);
		return (0);	// FATHER
	}
	if (lex->op.n_pipe > 0)
	{
		lex->lenght = 0;
		ft_execute(lex);
		if (ft_pipe(lex, lex->tokens, 0, 0) != -1)
		{
			waitpid(pid, &lex->return_value, 0);
			free(lex->op.pipe);
			free(lex->op.redirect);
			exit (0);
		}
	}
	else
		lex->args = lex->tokens;
	return (1);		// CHILD
}

int	ft_execute(t_lexer *lex)
{
	if (!ft_init_pipe(lex))
		return (0);
	if (lex->tokens)
	{
		if (ft_check_builtin(lex))
		{
			lex->return_value = ft_exec_builtin(lex);
			if (lex->can_return == true)
			{
				free(lex->cwd);
				free(lex->op.pipe);
				free(lex->op.redirect);
				ft_free_matrix(lex->tokens);
				ft_free_matrix(lex->paths);
				ft_free_matrix(lex->env_copy);
				return (lex->return_value);
			}
		}
		else if(ft_check_is_executable(lex) && ft_check_syntax_error(lex))
			ft_exec_path(lex);
		else
		{
			printf("%s: not a command\n", lex->tokens[0]);
			lex->return_value = 127;
		}
	}
	else
	{
		printf("bash: Missing command\n");
		lex->return_value = 1;
	}
	if (lex->is_executing)
		exit (0);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
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
				return (lex.return_value);
			}
		}
		free(prompt);
		lex.tokens = ft_tokenize(input, &lex);
		lex.is_executing = false;
		if (ft_execute(&lex))
		{
			free(input);
			return (lex.return_value);
		}
		if (input[0])
			add_history(input);
		ft_free_matrix(lex.tokens);
	}
	return (0);
}

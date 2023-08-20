/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 21:04:26 by CUOGL'attim      ###   ########.fr       */
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

void	ft_init_main(t_lexer *lex, char **env)
{
	lex->stds.stdin = dup(STDIN_FILENO);
	lex->stds.stdout = dup(STDOUT_FILENO);
	lex->env_copy = ft_copy_env(env);
	lex->paths = ft_path_splitter(lex);
	lex->absolute_path = false;
	lex->cwd = getcwd(NULL, 0);
	lex->pipe_num = 0;
	lex->return_value = 0;
	lex->op.pipe = NULL;
	lex->op.redirect = NULL;
}

bool	ft_minishell_exec(t_lexer *lex)
{
	lex->current_pipe = 0;
	lex->lenght = 0;
	lex->is_executing = false;
	lex->can_return = false;
	ft_execute(lex);
	if (lex->can_return == true)
	{
		ft_free_matrix(lex->tokens);
		ft_free_matrix(lex->args);
		return (1);
	}
	return (0);
}

void	ft_minishell(t_lexer *lex, char *argv)
{
	char	*input;

	while (1)
	{
		input = ft_input(ft_create_prompt(lex, argv));
		if (!input)
			break ;
		lex->tokens = ft_tokenize(input, lex);
		if (!ft_empty_redirections(lex))
			if (ft_minishell_exec(lex))
				break ;
		if (input[0])
			add_history(input);
		ft_free_matrix(lex->tokens);
		ft_free((void **)&lex->op.pipe);
		ft_free((void **)&lex->op.redirect);
	}
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	t_lexer	lex;

	(void)argc;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_init_main(&lex, env);
	ft_minishell(&lex, argv[1]);
	ft_free((void **)&lex.op.pipe);
	ft_free((void **)&lex.op.redirect);
	ft_free((void **)&lex.cwd);
	ft_free_matrix(lex.paths);
	ft_free_matrix(lex.env_copy);
	return (lex.return_value);
}

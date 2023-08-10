/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:28:01 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/10 21:35:41 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_matrix_shell(t_lexer *lex)
{
	int	i;
	int	lenght;
	int	n_temp;

	lenght = 0;
	i = 0;
	while (lex->tokens[i])
	{
		// echo ciao > out mondo][ echo ciao ">" out 
		if (lex->tokens[i][0] == '|') // | => "|" // || => "||"
		{
			n_temp = 0;
			while (lex->op.pipe[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.pipe[n_temp])
					break ;
				n_temp++;
			}
			if (lex->op.pipe[n_temp] && i + lex->lenght == lex->op.pipe[n_temp])
				break ;

		}
		if (lex->tokens[i][0] == '>' || lex->tokens[i][0] == '<')
		{
			n_temp = 0;
			while (lex->op.redirect[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.redirect[n_temp])
				{
					lenght -= 1;
					if (lex->tokens[i + 1] != NULL)
						lenght -= 1;
					break ;
				}
				n_temp++;
			}
		}
		i++;
	}
	lenght += i;
	return (lenght);
}

char	**ft_matrix_shell(t_lexer *lex)
{
	char	**matrix;
	int		i;
	int		len_matrix;
	int		n_temp;

	if (!lex->tokens)
		return (NULL);
	matrix = malloc(sizeof(char *) * ft_len_matrix_shell(lex) + 1);
	len_matrix = 0;
	i = 0;
	while (lex->tokens[i])	// echo ciao >> ciao < text qualcosa
	{
		if (lex->tokens[i][0] == '>' || lex->tokens[i][0] == '<')
		{
			n_temp = 0;
			while (lex->op.redirect[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.redirect[n_temp])
					i += 2;
				n_temp++;
			}
		}
		if (lex->tokens[i] == NULL)
			break ;
		if (lex->tokens[i][0] == '|')
		{
			n_temp = 0;
			while (lex->op.pipe[n_temp] > -1)
			{
				if (i + lex->lenght == lex->op.pipe[n_temp])
					break ;
				n_temp++;
			}
			if (lex->op.pipe[n_temp] && i + lex->lenght == lex->op.pipe[n_temp])
				break ;
		}
		matrix[len_matrix] = ft_strdup(lex->tokens[i]);
		len_matrix++;
		i++;
	}
	matrix[len_matrix] = NULL;
	return (matrix);
}

int	ft_pipe(t_lexer *lex, char **tokens, int old_fd, int more)
{
	int	pipe_fd[2];
	int	pid1;
	int	i;

	lex->tokens = tokens;
	if (!tokens || !lex->env_copy)
		return (0);
	if (!tokens[0])
	{
		printf("bash: Missing command\n");
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		return (1);
	if (more)
		if (dup2(old_fd, STDIN_FILENO) < 0)
			return (2);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		return (3);
	close(pipe_fd[1]);
	// ft_perror("Current Lenght|Pipe_Pos|Pipe_Num: %d|%d|%d\n", lex->lenght, lex->op.pipe[lex->op.n_pipe - 1], lex->op.n_pipe);
	if (lex->op.n_pipe == 0 || lex->lenght > lex->op.pipe[lex->op.n_pipe - 1])
		dup2(lex->stds.stdout, STDOUT_FILENO);
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_perror("ERROR: pipe can't store fds\n");
		return (1);
	}
	if (pid1 == 0)
		return (-1);	// -1 for execve
	waitpid(pid1, 0, 0);
	dup2(lex->stds.stdin, STDIN_FILENO);
	dup2(lex->stds.stdout, STDOUT_FILENO);
	// printf("PADRE OK!\n");
	i = ft_len_matrix_shell(lex) + 1;
	lex->lenght += i;
	if (tokens[i - 1] && tokens[i])
		return (ft_pipe(lex, &tokens[i], pipe_fd[0], more + 1));
	return (0);

}
// if (pipe(pipedes) == -1)
// 	ft_perror("ERROR: pipe can't store fds\n");

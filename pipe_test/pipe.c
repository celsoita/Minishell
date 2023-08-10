/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:17:10 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/10 15:57:17 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../minishell.h"

/*
	echo ciao sono fabio io >> qualcosa |
	len = 1
	len == minore(pipe[i] {7, 1} redirects[i] {5, 0})
*/
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
	printf("%d\n", lenght);
	return (lenght);
}

// char	**ft_cmatrix(char **tokens, char c)
// {
// 	char	**matrix;
// 	int		i, j;
//
// 	if (!tokens)
// 		return (NULL);
// 	matrix = malloc(sizeof(char *) * ft_len_cmatrix(tokens, c) + 1);
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		matrix[i] = malloc(sizeof(char) * strlen(tokens[i]) + 1);
// 		j = 0;
// 		while (tokens[i][j])
// 		{
// 			if (tokens[i][j] == c)
// 				break ;
// 			matrix[i][j] = tokens[i][j];
// 			j++;
// 		}
// 		matrix[i][j] = '\0';
// 		if (tokens[i][j] == c)
// 			break ;
// 		i++;
// 	}
// 	if (matrix[i] && matrix[i][0] == '\0')
// 		free(matrix[i]);
// 	matrix[i] = NULL;
// 	return (matrix);
// }

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

int	ft_our_code(char **tokens, char **env, t_stds std, int old_fd, int more, int lenght)
{
	char	**args;
	int	pipe_fd[2];
	int	pid1;
	int	i;
	t_lexer	lex;

	lex.tokens = tokens;
	lex.lenght = lenght;
	lex.op.redirect = malloc(sizeof(int) * 1);
	// lex.op.redirect[0] = malloc(sizeof(int *) * 2);
	// lex.op.redirect[0][0] = 1;
	// lex.op.redirect[0][1] = 0;
	lex.op.redirect[0] = -1;
	lex.op.n_pipe = 1;
	lex.op.pipe = malloc(sizeof(int) * (lex.op.n_pipe + 1));
	lex.op.pipe[0] = 1;
	// lex.op.pipe[1] = 4;
	lex.op.pipe[1] = -1;

	if (!tokens || !env)
		return (0);
	if (!tokens[0])
	{
		printf("bash: Missing command\n");
		return (1);
	}
	args = ft_matrix_shell(&lex);
	if (pipe(pipe_fd) == -1)
		return (1);
	if (more)
		if (dup2(old_fd, STDIN_FILENO) < 0)
			return (2);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		return (3);
	close(pipe_fd[1]);
	if (lex.op.n_pipe == 0 || lenght > lex.op.pipe[lex.op.n_pipe - 1])
		dup2(std.stdout, STDOUT_FILENO);
	pid1 = fork();
	if (pid1 < 0)
		return (4);
	if (pid1 == 0)
	{
		execve(tokens[0], args, env);
		exit(5);
	}
	waitpid(pid1, 0, 0);
	dup2(std.stdin, STDIN_FILENO);
	dup2(std.stdout, STDOUT_FILENO);
	printf("PADRE OK!\n");
	ft_free_matrix(args);
	i = ft_len_matrix_shell(&lex) + 1;
	if (tokens[i - 1] && tokens[i])
		return (ft_our_code(&tokens[i], env, std, pipe_fd[0], more + 1, lenght + i));
	return (0);
}

int main (int argc, char *argv[], char **env)
{
	int		retval;
	char	*tokens[5];
	t_stds	std;

	(void)argc;
	(void)argv;
	std.stdin = dup(STDIN_FILENO);	//.
	std.stdout = dup(STDOUT_FILENO);	//.
	tokens[0] = "/usr/bin/ls";
	tokens[1] = "|";
	tokens[2] = "/usr/bin/cat";
	tokens[3] = "file.txt";
	// tokens[4] = "|";
	// tokens[5] = "/usr/bin/wc";
	tokens[4] = NULL;
	retval = ft_our_code(tokens, env, std, 0, 0, 0);
	printf("RETURN: %d\n", retval);
	return (retval);
}

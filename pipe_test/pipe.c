/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:17:10 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/09 13:20:30 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../minishell.h"

typedef struct s_std
{
	int	in;
	int	out;
}	t_std;

// int	ft_len_cmatrix(char **tokens, char c)
// {
// 	int	i, j;
//
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		j = -1;
// 		while (tokens[i][++j])
// 			if (tokens[i][j] == c)
// 				break ;
// 		if (tokens[i][j] == c)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

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
			while (lex->op.pipe[n_temp])
			{
				if (i + lex->lenght == lex->op.pipe[n_temp][0])
					break ;
				n_temp++;
			}
			if (lex->op.pipe[n_temp] && i + lex->lenght == lex->op.pipe[n_temp][0])
				break ;

		}
		if (lex->tokens[i][0] == '>' || lex->tokens[i][0] == '<')
		{
			n_temp = 0;
			while (lex->op.redirect[n_temp])
			{
				if (i + lex->lenght == lex->op.redirect[n_temp][0])
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
			while (lex->op.redirect[n_temp])
			{
				if (i + lex->lenght == lex->op.redirect[n_temp][0])
					i += 2;
				n_temp++;
			}
		}
		if (lex->tokens[i] == NULL)
			break ;
		if (lex->tokens[i][0] == '|')
		{
			n_temp = 0;
			while (lex->op.pipe[n_temp])
			{
				if (i + lex->lenght == lex->op.pipe[n_temp][0])
					break ;
				n_temp++;
			}
			if (lex->op.pipe[n_temp] && i + lex->lenght == lex->op.pipe[n_temp][0])
				break ;
		}
		matrix[len_matrix] = ft_strdup(lex->tokens[i]);
		len_matrix++;
		i++;
	}
	matrix[len_matrix] = NULL;
	return (matrix);
}

int	ft_our_code(char **tokens, char **env, t_std std, int old_fd, int more, int *commands_index[2], int lenght)
{
	char	**args;
	int	pipe_fd[2];
	int	pid1;
	int	i;
	t_lexer	lex;

	lex.tokens = tokens;
	lex.lenght = lenght;
	lex.op.redirect = malloc(sizeof(int **) * 2);
	lex.op.redirect[0] = malloc(sizeof(int *) * 2);
	lex.op.redirect[0][0] = 1;
	lex.op.redirect[0][1] = 0;
	lex.op.redirect[1] = NULL;
	lex.op.pipe = malloc(sizeof(int **) * 2);
	lex.op.pipe[0] = malloc(sizeof(int *) * 2);
	lex.op.pipe[0][0] = 3;
	lex.op.pipe[0][1] = 0;
	lex.op.pipe[1] = NULL;

	if (!tokens || !tokens[0] || !env)
		return (0);
	args = ft_matrix_shell(&lex);
	if (pipe(pipe_fd) == -1)
		return (1);
	if (more)
		if (dup2(old_fd, STDIN_FILENO) < 0)
			return (2);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		return (3);
	close(pipe_fd[1]);
	if (!commands_index[more])
	{
		dup2(std.out, STDOUT_FILENO);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (4);
	if (pid1 == 0)
	{
		execve(tokens[0], args, env);
		exit(5);
	}
	waitpid(pid1, 0, 0);
	dup2(std.in, STDIN_FILENO);
	dup2(std.out, STDOUT_FILENO);
	printf("PADRE OK!\n");
	ft_free_matrix(args);
	i = ft_len_matrix_shell(&lex) + 1;
	if (tokens[i - 1] && tokens[i])
		return (ft_our_code(&tokens[i], env, std, pipe_fd[0], more + 1, commands_index, lenght + i));
	return (0);
}

int main (int argc, char *argv[], char **env)
{
	int		retval;
	char	*tokens[6];
	int		**commans_index;
	t_std	std;

	(void)argc;
	(void)argv;
	std.in = dup(STDIN_FILENO);	//.
	std.out = dup(STDOUT_FILENO);	//.
	tokens[0] = "/usr/bin/ls";
	tokens[1] = ">";
	tokens[2] = "file.txt";
	tokens[3] = "|";
	tokens[4] = "/usr/bin/wc";
	tokens[5] = NULL;
	commans_index = malloc(sizeof(int *) * 2);
	commans_index[0] = malloc(sizeof(int) * 2);
	commans_index[0][0] = 2;
	commans_index[0][1] = 0;
	commans_index[1] = NULL;
	retval = ft_our_code(tokens, env, std, 0, 0, commans_index, 0);
	free(commans_index[0]);
	free(commans_index);
	printf("RETURN: %d\n", retval);
	return (retval);
}

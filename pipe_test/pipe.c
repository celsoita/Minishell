/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:17:10 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/08 13:02:01 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../minishell.h"

int	ft_code_vault(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	int	pid1= fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{	//child process 1
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com",NULL);
	}
	int	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

typedef struct s_std
{
	int	in;
	int	out;
}	t_std;

int	ft_len_cmatrix(char **tokens, char c)
{
	int	i, j;

	i = 0;
	while (tokens[i])
	{
		j = -1;
		while (tokens[i][++j])
			if (tokens[i][j] == c)
				break ;
		if (tokens[i][j] == c)
			break ;
		i++;
	}
	return (i);
}

char	**ft_cmatrix(char **tokens, char c)
{
	char	**matrix;
	int		i, j;

	if (!tokens)
		return (NULL);
	matrix = malloc(sizeof(char *) * ft_len_cmatrix(tokens, c));
	i = 0;
	while (tokens[i])
	{
		matrix[i] = malloc(sizeof(char) * strlen(tokens[i]) + 1);
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == c)
				break ;
			matrix[i][j] = tokens[i][j];
			j++;
		}
		matrix[i][j] = '\0';
		if (tokens[i][j] == c)
			break ;
		i++;
	}
	if (matrix[i] && matrix[i][0] == '\0')
		free(matrix[i]);
	matrix[i] = NULL;
	return (matrix);
}

char	**ft_new_matrix(char **args, int fd)
{
	// Fai cose
	// CIoe' cose
	// si, leggi dal fd e aggiungilo alle vecchie args
	return (matrix);
}

int	ft_our_code(char **tokens, char **env, t_std std, bool more)
{
	char	**args;
	int	pipe_fd[2];
	int	pid1;
	int	i;
	int	j;

	if (!tokens || !tokens[0] || !env)
		return (0);
	args = ft_cmatrix(tokens, '|');
	if (pipe(pipe_fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		i = open("out", 777, O_WRONLY);
		if (dup2(i, STDOUT_FILENO) < 0)
			return (3);
		close(i);
		// if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		// 	return (3);
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		if (more)
			args = ft_new_matrix(args, pipe_fd[0]);
		execve(tokens[0], args, env);
		(void)env;
		exit(0);
	}
	waitpid(pid1, 0, 0);

	// char *line;
	// line = get_next_line(pipe_fd[1]);
	// while (line)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(pipe_fd[1]);
	// }
	// printf("\n");
	
	printf("PADRE OK!\n");
	free(args);
	dup2(std.in, STDIN_FILENO);
	dup2(std.out, STDOUT_FILENO);
	(void)j;
	i = ft_len_cmatrix(tokens, '|') + 1;
	if (tokens[i - 1] && tokens[i])
		return (ft_our_code(&tokens[i], env, std, true));
	return (0);
	// i = 1;
	// while (tokens[i])
	// {
	// 	j = -1;
	// 	while (tokens[i][++j])
	// 		if (tokens[i][j] == '|')
	// 			return (ft_our_code(&tokens[i + 1], env, std));
	// 	i++;
	// }
	// return (0);
}

int main (int argc, char *argv[], char **env)
{
	int		retval;
	char	*tokens[5];
	t_std	std;

	(void)argc;
	(void)argv;
	std.in = dup(STDIN_FILENO);
	std.out = dup(STDOUT_FILENO);
	tokens[0] = "/usr/bin/cat";
	tokens[1] = "file.txt";
	tokens[2] = "|";
	tokens[3] = "/usr/bin/less";
	tokens[4] = NULL;
	retval = ft_our_code(tokens, env, std, false);
	printf("RETURN: %d\n", retval);
	return (retval);
}

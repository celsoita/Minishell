/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:17:10 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/07 20:35:48 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

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

typedef struct s_stds
{
	int	in;
	int	out;
}	t_stds;

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
		i++;
	}
	return (i);
}

char	**ft_cmatrix(char **tokens, char c)
{
	char	**matrix;
	int		i, j;

	matrix = malloc(sizeof(char *) * ft_len_cmatrix(tokens, c) + 1);
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
	// if (tokens[i][0] == '\0')
	// {
	// 	free(tokens[i]);
	// 	tokens[i] = NULL;
	// }
	tokens[i + 1] = NULL;
	return (matrix);
}

int	ft_our_code(char **tokens, char **env, t_stds stds)
{
	char	**args;
	int	pipe_fd[2];
	int	pid1;
	int	i, j;

	args = ft_cmatrix(&tokens[1], '|');
	if (pipe(pipe_fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		printf("FIGLIO DENTRO!\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(tokens[0], args, env);
	}
	waitpid(pid1, 0, 0);
	printf("PADRE OK!\n");
	free(args);

	dup2(stds.in, STDIN_FILENO);
	dup2(stds.out, STDOUT_FILENO);
	i = 1;
	while (tokens[i])
	{
		j = -1;
		while (tokens[i][++j])
			if (tokens[i][j] == '|')
				return (ft_our_code(&tokens[i + 1], env, stds));
		i++;
	}
	return (0);
}

int main (int argc, char *argv[], char **env)
{
	int		retval;
	char	*tokens[5];
	t_stds	stds;

	(void)argc;
	(void)argv;
	stds.in = dup(STDIN_FILENO);
	stds.out = dup(STDOUT_FILENO);
	tokens[0] = "/usr/bin/cat";
	tokens[1] = "file.txt";
	tokens[2] = "|";
	tokens[3] = "/usr/bin/less";
	tokens[4] = NULL;
	retval = ft_our_code(tokens, env, stds);
	printf("RETURN: %d\n", retval);
	return (retval);
}

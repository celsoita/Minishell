/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_little_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:50:19 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/08 11:50:55 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//questo e' uno strjoin modificato per unire i path
char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	
	while(s1[i])
	{
		res[i] =s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while(s2[j])
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return(res);
}

// char	**ft_clean_pipe(t_lexer *lex)
// {
// 	int	y;
// 	int	x;
// 	int	j;
// 	int lenght_str;
// 	char	**new_tokens;
// 	new_tokens = malloc(sizeof(char *) * ft_strlen_matrix(lex->tokens - lex->pipe_num) + 1);
// 	lenght_str = 0;
// 	y = 0;
// 	j = 0;
// 	/*
// 		devo pulire la pipe e se dopo la pipe ci sta un comando metto una flag per far eseguire al execve il comando
// 		esempio ls | cat main.c
// 		if (tokens[] == " |" && ( if (!access(tokens[i + 1 di path try], F_OK)))
// 		{
// 			so che dopo devo eseguire un certo numero di comandi e quindi quando storage il token

// 			tecnicamente  abbiamo gia rilevato la presenza di un pipe e di conseguenza  sappiamo dove mettere l'input 
			
// 			nel nuovo token so che deve essere eseguito 
// 		}

// 	ls -la | cat main.c | grep "casa" 	
// 	*/
// 	while (lex->tokens[y])
// 	{
// 		x = 0;
// 		if (!ft_strncmp(lex->tokens[y],"|", 1))
// 			y++;
// 		lenght_str =  ft_strlen(lex->tokens[y]);
// 		new_tokens[j] = malloc(sizeof(char ) * lenght_str + 1);
// 		while (x < lenght_str)
// 		{
// 			new_tokens[j][x] = lex->tokens[y][x];
// 			x++;
// 		}
// 		new_tokens[j][x] = '\0';
// 		y++;
// 		j++;
// 	}
// 	new_tokens[j] = NULL;
// 	// ft_free_matrix(lex->tokens);
// return (new_tokens);
// }
// questa funzione prova i path in bruteforce
void	ft_exec_path(t_lexer *lex)
{
	char *path_try;
	int	i;
	pid_t pid;

	i = 0;
	i = ft_strlen_matrix(lex->paths);
	/*
	se uno dei token == '|'
		allora tu fai dup2 di
	*/
	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, 0, 0);
		return ;
	}
	if (lex->pipe_num > 0)
	{
			ft_pipe(lex);
	}
	if (!lex->absolute_path)
	{
		while(i--)
		{
			path_try = ft_strjoin_path(lex->paths[i],lex->tokens[0]);
			if (!access(path_try, F_OK))
			{
				execve(path_try, lex->tokens, lex->env_copy);
				free(path_try);
				exit (0);
			}
			free(path_try);
		}
	}
	else
	{
		execve(lex->tokens[0], lex->tokens, lex->env_copy);
		exit (0);
	}
}

void	sigint_handler()
{
	rl_on_new_line();
	write(1,"\n", 1);
}

bool ft_path_try(t_lexer *lex)
{
	int	i;
	char *path_try;

	i = 0;
	i = ft_strlen_matrix(lex->paths);
	while(i--)
	{
		path_try = ft_strjoin_path(lex->paths[i],lex->tokens[0]);
		if (!access(path_try, F_OK))
			return(1);
	}
	return (0);
}
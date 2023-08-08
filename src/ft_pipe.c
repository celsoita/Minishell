/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:28:01 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/08 10:28:42 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(t_lexer *lex)
{
	int		pipedes[2];
	char	*temp;

	lex->pipe_num -= 1;
	lex->stds.stdin = dup(STDIN_FILENO);
	lex->stds.stdout = dup(STDOUT_FILENO);

	if (pipe(pipedes) == -1)
		ft_perror("ERROR: pipe can't store fds\n");
	close(pipedes[0]);
	dup2(pipedes[1], STDOUT_FILENO);
	int	i = 1;
	temp = ft_strchr(lex->tokens[i], '|');
	while (lex->tokens[i] && !temp)
	{
		temp = ft_strchr(lex->tokens[i], '|');
		i++;
	}
	free(lex->tokens[0]);
	lex->tokens[0] = lex->tokens[i];
}


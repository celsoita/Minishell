/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:18:09 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 15:55:35 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_redirects_exist(t_lexer *lex, int *i)
{
	if (lex->op.pipe[lex->current_pipe] != -1 && \
	lex->op.redirect[lex->current_redirect] > lex->op.pipe[lex->current_pipe])
		return (1);
	if (lex->current_redirect >= lex->op.n_redirect)
		return (1);
	*i = lex->op.redirect[lex->current_redirect] - lex->lenght;
	if (lex->tokens[(*i) + 1] == NULL)
	{
		lex->current_redirect++;
		return (1);
	}
	return (0);
}

void	ft_heredoc(t_lexer *lex, char **buffer, int *fd, int *i)
{
	*fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	*buffer = NULL;
	while (ft_strlen((*buffer)) - 1 != ft_strlen(lex->tokens[(*i) + 1]) || \
	ft_strncmp((*buffer), lex->tokens[(*i) + 1], ft_strlen((*buffer)) - 1))
	{
		if ((*buffer))
		{
			write((*fd), (*buffer), ft_strlen((*buffer)));
			if (ft_strchr((*buffer), EOF))
				break ;
			ft_free((void **)&(*buffer));
		}
		ft_putstr_fd("> ", lex->stds.stdout);
		*buffer = get_next_line(lex->stds.stdin);
		if ((*buffer) == NULL)
		{
			ft_putchar_fd('\n', lex->stds.stdout);
			break ;
		}
	}
	ft_free((void **)&(*buffer));
	close((*fd));
	*buffer = ".temp";
}

void	ft_redirects_found(t_lexer *lex, int *i)
{
	char	*buffer;
	int		fd;

	if (lex->tokens[(*i)][0] == '<' && lex->tokens[(*i)][1] == '\0')
		buffer = lex->tokens[(*i) + 1];
	else if (lex->tokens[(*i)][0] == '<' && lex->tokens[(*i)][1] == '<')
		ft_heredoc(lex, &buffer, &fd, i);
	else if (lex->tokens[(*i)][0] == '>' && lex->tokens[(*i)][1] == '\0')
		fd = open(lex->tokens[(*i) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (lex->tokens[(*i)][0] == '>' && lex->tokens[(*i)][1] == '>')
		fd = open(lex->tokens[(*i) + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (lex->tokens[(*i)][0] == '<')
	{
		fd = open(buffer, O_RDONLY, 0777);
		dup2(fd, STDIN_FILENO);
	}
	else if (lex->tokens[(*i)][0] == '>')
		dup2(fd, STDOUT_FILENO);
	lex->current_redirect++;
}

/* REDIRECTIONS: '>' '>>' '<' '<<' */
void	ft_redirects(t_lexer *lex)
{
	int		i;

	if (ft_redirects_exist(lex, &i))
		return ;
	ft_redirects_found(lex, &i);
	ft_redirects(lex);
}

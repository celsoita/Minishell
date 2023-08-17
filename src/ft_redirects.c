/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:18:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/17 18:09:50 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	"<"
		PRENDE IL ARGOMENTO CON OPEN
			'cat < ciao2' => ciao
	"<<"
		PRENDE INPUT DAL HEREDOC
			cat << here
			cat ciao | cat << here
			echo ciao | cat << here
		PRENDE PRIMA IL PRIMO E DOPO IL SECONDO
			cat << here1 > ciao | cat << here2
		NON PRENDE L'INPUT SE HA UN ARGOMENTO
			cat << here1 ciao2 >> ciao
	">" e ">>"
		SCRIVE TUTTO NEL ARGOMENTO DI ">"/">>"
			cat ciao2 ciao2 ciao2 ciao2 > ciaofile.txt
		NON LO PASSA AL STDOUT DEL "|" MA DEL ">"/">>"
			cat ciao2 > ciaofile.txt | cat
*/

void	ft_redirects(t_lexer *lex)
{
	char	*buffer;
	int		fd;
	int		i;

	ft_perror("DEBUG: current_pipe[%d](%d)\n", lex->current_pipe, lex->op.pipe[lex->current_pipe]);
	if (lex->op.pipe[lex->current_pipe] != -1 && lex->op.redirect[lex->current_redirect] > lex->op.pipe[lex->current_pipe])
		return ;
	ft_perror("DEBUG: current_redirect[%d](%d)\n", lex->current_redirect, lex->op.redirect[lex->current_redirect]);
	if (lex->current_redirect >= lex->op.n_redirect)
		return ;
	ft_perror("DEBUG: token[lenght(%d)](%s) == redirect[current_redirect(%d)](%d)\n", lex->lenght, lex->tokens[lex->lenght], lex->current_redirect, lex->op.redirect[lex->current_redirect] - lex->lenght); // REMOVE
	i = lex->op.redirect[lex->current_redirect] - lex->lenght;
	ft_perror("DEBUG: current_redirect[pos(%d)](%s)\n", i, lex->tokens[i]);
	//"<"	INPUT
	if (lex->tokens[i][0] == '<' && lex->tokens[i][1] == '\0')
		buffer = lex->tokens[i + 1];
	//"<<"	HEREDOC
	else if (lex->tokens[i][0] == '<' && lex->tokens[i][1] == '<')
	{
		fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		buffer = NULL;
		ft_perror("HEREDOC ARGUMENT(%s)\n", lex->tokens[i + 1]);
		while (ft_strlen(buffer) - 1 != ft_strlen(lex->tokens[i + 1]) || ft_strncmp(buffer, lex->tokens[i + 1], ft_strlen(buffer) - 1))
		{
			// ft_perror("STRCMP(%d)\n", ft_strncmp(buffer, lex->tokens[i + 1], ft_strlen(buffer) - 1));
			if (buffer)
			{
				write(fd, buffer, ft_strlen(buffer));
				if (ft_strchr(buffer, EOF))
					break ;
				free(buffer);
			}
			ft_putstr_fd("> ", lex->stds.stdout);
			buffer = get_next_line(lex->stds.stdin);
			if (buffer == NULL)
				break ;
		}
		free(buffer);
		close(fd);
		buffer = ".temp";
	}
	//">"	WRITE
	else if (lex->tokens[i][0] == '>' && lex->tokens[i][1] == '\0')
		fd = open(lex->tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	//">>"	APPEND
	else if (lex->tokens[i][0] == '>' && lex->tokens[i][1] == '>')
		fd = open(lex->tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);

	if (lex->tokens[i][0] == '<')
	{
		fd = open(buffer, O_RDONLY, 0777);
		dup2(fd, STDIN_FILENO);
	}
	else if (lex->tokens[i][0] == '>')
		dup2(fd, STDOUT_FILENO);
	lex->current_redirect++;
	ft_redirects(lex);
}

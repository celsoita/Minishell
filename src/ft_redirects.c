/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:18:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/17 12:20:19 by cschiavo         ###   ########.fr       */
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
	//"<"
		// open("ciao2", O_CREAT | O_RDONLY, 0777);
	//"<<"
		char	*buffer;
		int		fd;
		int		i;
		int		j;
		int		k;

		i = 0;
		j = 0;
		while (j < lex->op.n_redirect && lex->tokens[i])	//{1, 7, -1}
		{
			printf("DEBUG: lenght(%d) + i(%d) == redirect[%d](%d)\n", lex->lenght, i, j, lex->op.redirect[j]);
			// HEREDOC
			if (lex->lenght + i == lex->op.redirect[j] && lex->tokens[i][1] == '<')
				break ;
			i++;
			// printf("AUMENTO DI 1 i(%d)\n", i);
			k = 0;
			if (lex->current_pipe < lex->op.n_pipe)	//{5, -1}
			{
				if (lex->lenght + i == lex->op.pipe[k])
				{
					j++;
					i = 0;
					break ;
				}	
				k++;
				// printf("AUMENTO DI 1 k(%d) e RESETTO i(%d) a 0\n", k, i);
			}
		}
		if (lex->lenght + i == lex->op.redirect[j] && lex->tokens[i][1] == '<')
		{
			fd = open(".temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
			buffer = NULL;
			printf("HEREDOC ARGUMENT(%s)\n", lex->tokens[i + 1]);
			while (ft_strlen(buffer) - 1 != ft_strlen(lex->tokens[i + 1]) || ft_strncmp(buffer, lex->tokens[i + 1], ft_strlen(buffer) - 1))
			{
				printf("STRCMP(%d)\n", ft_strncmp(buffer, lex->tokens[i + 1], ft_strlen(buffer) - 1));
				write(fd, buffer, ft_strlen(buffer));
				if (buffer)
				{
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
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	//">"
		// open("ciao2", O_CREAT | O_WRONLY, 0777);
	//">>"
		// open("ciao2", O_CREAT | O_APPEND, 0777);
}

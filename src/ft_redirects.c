/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:18:09 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/11 14:54:19 by cschiavo         ###   ########.fr       */
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
		int		i;
		int		j;
		int		k;

		i = 0;
		j = 0;
		while (j < lex->op.n_redirect)	//{1, 7, -1}
		{
			if (lex->lenght + i == lex->op.redirect[j] && lex->tokens[i][1] == '<')
				// HEREDOC
			i++;
			k = 0;
			while (k < lex->op.n_pipe)	//{5, -1}
			{
				if (lex->lenght + i == lex->op.pipe[k])
				{
					j++;
					i = 0;
					break ;
				}	
				k++;
			}
		}

		while (ft_strncmp(buffer, lex->args[]))
		read(lex->stds.stdin, buffer, 1);
	//">"
		// open("ciao2", O_CREAT | O_WRONLY, 0777);
	//">>"
		// open("ciao2", O_CREAT | O_APPEND, 0777);
}

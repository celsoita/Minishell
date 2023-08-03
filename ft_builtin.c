/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:07:44 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/03 19:31:16 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(t_lexer *lex)
{
	char	*old_cwd;
	int		return_value;

	old_cwd = lex->cwd;
	if (!lex->tokens[1])
		lex->cwd = ft_strdup("/nfs/homes/cschiavo");
	else
		lex->cwd = ft_strjoin_path(lex->cwd, lex->tokens[1]);
	free(old_cwd);
	old_cwd = NULL;
	return_value = chdir(lex->cwd);
	lex->cwd = getcwd(NULL, 0);
	return (return_value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:50:03 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 19:50:18 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_chdir_arg(t_lexer *lex)
{
	char	*old_cwd;

	old_cwd = lex->cwd;
	if (!lex->args[1])
		old_cwd = ft_expander(lex, "HOME");
	else
	{
		if (lex->args[1][0] == '/')
			old_cwd = ft_strdup(lex->args[1]);
		else if (lex->args[1][0] == '-')
		{
			if (lex->args[1][1] == '-')
				old_cwd = ft_expander(lex, "HOME");
			else
			{
				old_cwd = ft_expander(lex, "OLDPWD");
				printf("%s\n", old_cwd);
			}
		}
		else
			old_cwd = ft_strjoin_path(old_cwd, lex->args[1]);
	}
	return (old_cwd);
}

void	ft_change_expansions(t_lexer *lex)
{
	char	**old_pwd;

	old_pwd = ft_search_str_in_env(lex, "OLDPWD", \
		ft_strlen_matrix(lex->env_copy));
	free(*old_pwd);
	*old_pwd = malloc(sizeof(char) * (7 + ft_strlen(lex->cwd)) + 1);
	ft_strcpy(*old_pwd, "OLDPWD=");
	ft_strcpy(&(*old_pwd)[7], lex->cwd);
	ft_free((void **)&lex->cwd);
	lex->cwd = getcwd(NULL, 0);
	old_pwd = ft_search_str_in_env(lex, "PWD", ft_strlen_matrix(lex->env_copy));
	free(*old_pwd);
	*old_pwd = malloc(sizeof(char) * (4 + ft_strlen(lex->cwd)) + 1);
	ft_strcpy(*old_pwd, "PWD=");
	ft_strcpy(&(*old_pwd)[4], lex->cwd);
}

/*
	'-':	Return to OLDPWD
	'--':	Like '~' return to HOME
	'.':	Current dir
	'..':	Directory previous current
	'/':	Move to root
*/
void	ft_chdir(t_lexer *lex)
{
	char	*old_cwd;

	if (lex->op.n_pipe > 0)
	{
		if (lex->args[1] && lex->args[1][0] == '-')
		{
			old_cwd = ft_expander(lex, "OLDPWD");
			printf("%s\n", old_cwd);
			free(old_cwd);
		}
		return ;
	}
	if (ft_strlen_matrix(lex->args) - 1 > 1)
		return (ft_perror("cd: too many arguments\n"));
	old_cwd = ft_chdir_arg(lex);
	if (chdir(old_cwd) == -1)
		ft_perror("cd: %s: Not a directory\n", lex->args[1]);
	free(old_cwd);
	ft_change_expansions(lex);
}

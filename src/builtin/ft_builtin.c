/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:07:44 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 14:46:51 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_chdir(t_lexer *lex)
{
	char	*old_cwd;
	char	**old_pwd;

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
	if (chdir(old_cwd) == -1)
		ft_perror("cd: %s: Not a directory\n", lex->args[1]);
	free(old_cwd);

	// Change OLDPWD expansion
	old_pwd = ft_search_str_in_matrix(lex, "OLDPWD", ft_strlen_matrix(lex->env_copy));
	free(*old_pwd);
	*old_pwd = malloc(sizeof(char) * (7 + ft_strlen(lex->cwd)) + 1);
	ft_strcpy(*old_pwd, "OLDPWD=");
	ft_strcpy(&(*old_pwd)[7], lex->cwd);
	ft_free((void **)&lex->cwd);
	
	lex->cwd = getcwd(NULL, 0);
	
	// Change PWD expansion
	old_pwd = ft_search_str_in_matrix(lex, "PWD", ft_strlen_matrix(lex->env_copy));
	free(*old_pwd);
	*old_pwd = malloc(sizeof(char) * (4 + ft_strlen(lex->cwd)) + 1);
	ft_strcpy(*old_pwd, "PWD=");
	ft_strcpy(&(*old_pwd)[4], lex->cwd);
}

void	ft_echo(t_lexer *lex)
{
	int	i;

	if (!lex->args[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (!ft_strncmp(lex->args[1], "-n", 3))
		i++;
	if (lex->args[i])
	{
		printf("%s",lex->args[i]);
		i++;
		while (lex->args[i])
		{
			printf(" %s",lex->args[i]);
			i++;
		}
	}
	if (ft_strncmp(lex->args[1], "-n", 3))
		printf("\n");
}

char	*ft_expander(t_lexer *lex, char *str)
{
	char	**raw_pointer;
	char	*res;
	int	lenght;
	int	i;
	//$ciao$mondo
	lenght = ft_strlen_matrix(lex->env_copy);
	raw_pointer = ft_search_str_in_matrix(lex, str, lenght);
	if (!raw_pointer || !*raw_pointer)
		ft_free((void **)&raw_pointer);
	res = NULL;
	i = 0;
	while ((*raw_pointer)[i])
	{
		if ((*raw_pointer)[i] == '=')
		{
			i++;
			res = ft_strdup(&(*raw_pointer)[i]);
			break;
		}
		i++;
	}
	return (res);
}

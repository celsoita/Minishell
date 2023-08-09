/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:07:44 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/09 16:41:23 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_chdir(t_lexer *lex)
{
	char	*old_cwd;
	char	**old_pwd;

	if (ft_strlen_matrix(lex->tokens) - 1 > 1)
		return (ft_perror("cd: too many arguments\n"));
	old_cwd = lex->cwd;
	if (!lex->tokens[1])
		old_cwd = ft_expander(lex, "HOME");
	else
	{
		if (lex->tokens[1][0] == '/')
			old_cwd = ft_strdup(lex->tokens[1]);
		else if (lex->tokens[1][0] == '-')
		{
			if (lex->tokens[1][1] == '-')
				old_cwd = ft_expander(lex, "HOME");
			else
			{
				old_cwd = ft_expander(lex, "OLDPWD");
				printf("%s\n", old_cwd);
			}
		}
		else
			old_cwd = ft_strjoin_path(old_cwd, lex->tokens[1]);
	}
	if (chdir(old_cwd) == -1)
		ft_perror("cd: %s: Not a directory\n", lex->tokens[1]);
	free(old_cwd);

	// Change OLDPWD expansion
	old_pwd = ft_search_str_in_matrix(lex, "OLDPWD", ft_strlen_matrix(lex->env_copy));
	free(*old_pwd);
	*old_pwd = malloc(sizeof(char) * (7 + ft_strlen(lex->cwd)) + 1);
	ft_strcpy(*old_pwd, "OLDPWD=");
	ft_strcpy(&(*old_pwd)[7], lex->cwd);
	free(lex->cwd);
	lex->cwd = NULL;
	
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

	if (!lex->tokens[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (!ft_strncmp(lex->tokens[1], "-n", 3))
		i++;
	if (lex->tokens[i])
	{
		printf("%s",lex->tokens[i]);
		i++;
		while (lex->tokens[i])
		{
			printf(" %s",lex->tokens[i]);
			i++;
		}
	}
	if (ft_strncmp(lex->tokens[1], "-n", 3))
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
	{
		free(raw_pointer);
		return (NULL);
	}
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

void	ft_token_expander(t_lexer *lex)
{
	char	*str_temp;
	int		i;

	i = 0;
	while (lex->tokens[i])
	{
		if (lex->tokens[i][0] == '$')
		{
			str_temp = lex->tokens[i];
			lex->tokens[i] = ft_expander(lex, &lex->tokens[i][1]);
			if (!lex->tokens[i])
				lex->tokens[i] = str_temp;
			else
				free(str_temp);
		}
		i++;
	}
}

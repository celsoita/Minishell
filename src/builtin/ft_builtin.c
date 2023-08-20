/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:07:44 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 20:49:26 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	lex->flags:
	1:	echo
	2:	cd
	3:	pwd
	4:	export
	5:	unset
	6:	env
	7:	exit
*/
int	ft_exec_builtin(t_lexer *lex)
{
	lex->can_return = false;
	if (lex->flags == 1)
		ft_echo(lex);
	if (lex->flags == 2)
		ft_chdir(lex);
	if (lex->flags == 3)
		printf("%s\n", lex->cwd);
	if (lex->flags == 4)
		ft_export(lex);
	if (lex->flags == 5)
		ft_unset(lex, false);
	if (lex->flags == 6)
		ft_print_env(lex->env_copy, false);
	if (lex->flags == 7)
		ft_exit(lex);
	return (lex->return_value);
}

/*
	FLAGS:
		'-n':	Print in same line (NO '\n')
*/
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
		printf("%s", lex->args[i]);
		i++;
		while (lex->args[i])
		{
			printf(" %s", lex->args[i]);
			i++;
		}
	}
	if (ft_strncmp(lex->args[1], "-n", 3))
		printf("\n");
}

bool	ft_expander_check(t_lexer *lex, char *str, char ***raw_pointer)
{
	int	lenght;

	if (!str || !str[0])
		return (1);
	lenght = ft_strlen_matrix(lex->env_copy);
	*raw_pointer = ft_search_str_in_env(lex, str, lenght);
	if (!(*raw_pointer) || !*(*raw_pointer))
	{
		ft_free((void **)&(*raw_pointer));
		return (1);
	}
	return (0);
}

/*VARIABLES POSSIBILITIES!*/
//echo $PATH					-> /bin/...
//echo $PATH$PATH				-> /bin/.../bin/...
//echo "$PATH"					-> /bin/...
//echo '$PATH'					-> $PATH
//echo "'$PATH'"				-> '/bin/...'
//echo "'"'$PATH'"'"			-> '$PATH'
//echo "$PATH"ciao				-> /bin/...ciao
//echo $PATH(ft_alphanum())		-> 
//echo $PATH(!ft_alphanum())	-> /bin/...(!ft_alphanum())
char	*ft_expander(t_lexer *lex, char *str)
{
	char	**raw_pointer;
	char	*res;
	int		i;

	raw_pointer = NULL;
	if (ft_expander_check(lex, str, &raw_pointer))
		return (NULL);
	res = NULL;
	i = 0;
	while ((*raw_pointer)[i])
	{
		if ((*raw_pointer)[i] == '=')
		{
			i++;
			res = ft_strdup(&(*raw_pointer)[i]);
			break ;
		}
		i++;
	}
	return (res);
}

void	ft_exit(t_lexer *lex)
{
	lex->can_return = true;
	if (lex->args[1])
	{
		if (lex->args[2])
		{
			ft_perror("bash: exit: too many argument\n");
			lex->can_return = false;
			lex->return_value = 1;
		}
		else
			lex->return_value = ft_atoi(lex->args[1]) % 256;
	}
	printf("exit\n");
}

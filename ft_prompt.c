/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:24:48 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/27 18:38:26 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_prompt_username(void)
{
	char	*username = getenv("USER");
	char	cwd[1024];
	char	*raw_hostname;
	char	*hostname;
	int	fd;
	int	i;

	fd = open("/etc/hostname",O_RDONLY);
	raw_hostname = get_next_line(fd);
	
	i = 0;
	while(raw_hostname[i] != '.')
		i++;
	hostname = malloc(sizeof(char) * i +1);
	i = 0;
	while(raw_hostname[i] != '.')
	{
		hostname[i] = raw_hostname[i];
		i++;
	}
	hostname[i] = '\0';
	//cschiavo@c2r4p11:~/Desktop/Minishell/Minishell$
	getcwd(cwd, sizeof(cwd));
	printf("\e[1;32m%s\e[0m@%s:~%s$",username, hostname, cwd);
	//\e[1;34mis sleeping\e[0m
}
void	ft_clear_screen(void)
{
	char *clear_seq = "\e[H\e[2J";
	tputs(clear_seq, 1, putchar);
}
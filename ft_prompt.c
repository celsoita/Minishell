/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:24:48 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/03 16:54:22 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_prompt_username(void)
{
	char	*username;
	char	*raw_hostname;
	char	*hostname;
	char	*res;
	char	*str_temp;
	int		fd;
	int		i;

	username = getenv("USER");
	fd = open("/etc/hostname",O_RDONLY);
	raw_hostname = get_next_line(fd);
	close(fd);
	
	i = 0;
	while(raw_hostname[i] != '.')
		i++;
	hostname = malloc(sizeof(char) * i + 1);
	i = 0;
	while(raw_hostname[i] != '.')
	{
		hostname[i] = raw_hostname[i];
		i++;
	}
	hostname[i] = '\0';
	res = ft_strjoin("\e[0m@", hostname);
	free(hostname);
	hostname = ft_strjoin("\e[1;32m", username);
	str_temp = ft_strjoin(hostname, res);
	free(hostname);
	free(res);
	res = ft_strjoin(str_temp, ": ");
	free(str_temp);
	free(raw_hostname);
	return(res);
}

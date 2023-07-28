/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:01:44 by cschiavo          #+#    #+#             */
/*   Updated: 2022/12/09 09:58:04 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_remove_line(char *buff)
{
	char	*buff_fresh;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (buff[i] == 0)
	{
		free(buff);
		return (0);
	}
	buff_fresh = ft_calloc(ft_strlen(buff) - i + 1, sizeof(char));
	i++;
	while (buff[i] != '\0')
		buff_fresh[j++] = buff[i++];
	free(buff);
	return (buff_fresh);
}

static char	*ft_get_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (buff[i] == '\0')
		return (0);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_free_join(char *buff, char *tmp)
{
	char	*buff_fresh;

	buff_fresh = ft_strjoin(buff, tmp);
	free(buff);
	return (buff_fresh);
}

static char	*ft_read_file(char *buff, int fd)
{
	char	*tmp;
	int		i;

	i = 1;
	if (buff == 0)
		buff = ft_calloc(1, 1);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (i > 0)
	{
		if (ft_strchr(buff, '\n') != 0)
			break ;
		i = read(fd, tmp, BUFFER_SIZE);
		if (i < 0)
		{
			free(tmp);
			return (0);
		}
		tmp[i] = '\0';
		buff = ft_free_join(buff, tmp);
	}
	free(tmp);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[FOPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	buff[fd] = ft_read_file(buff[fd], fd);
	line = ft_get_line(buff[fd]);
	buff[fd] = ft_remove_line(buff[fd]);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famirant <famirant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:09:11 by famirant          #+#    #+#             */
/*   Updated: 2023/08/19 13:28:09 by famirant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gnl_strjoin(char *llist, char *buff)
{
	char	*nstr;
	size_t	i;
	size_t	j;

	if (!llist)
	{
		llist = malloc(1);
		llist[0] = '\0';
	}
	if (!llist || !buff)
		return (NULL);
	nstr = malloc(ft_strlen(llist) + ft_strlen(buff) + 1);
	if (!nstr)
		return (NULL);
	i = -1;
	while (llist[++i])
		nstr[i] = llist[i];
	j = 0;
	while (buff[j])
		nstr[i++] = buff[j++];
	nstr[i] = '\0';
	free (llist);
	return (nstr);
}

char	*ft_get_line(char *lline)
{
	int		i;
	char	*str;

	i = 0;
	if (!lline[i])
		return (NULL);
	while (lline[i] && lline[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (lline[i] && lline[i] != '\n')
	{
		str[i] = lline[i];
		i++;
	}
	if (lline[i] == '\n')
	{
		str[i] = lline[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_line(char *lline)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (lline[i] && lline[i] != '\n')
		i++;
	if (lline[i] == '\n')
		i++;
	if (!lline[i])
	{
		free(lline);
		return (NULL);
	}
	str = malloc(ft_strlen(lline) - i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (lline[i])
		str[j++] = lline[i++];
	str[j] = '\0';
	free (lline);
	return (str);
}

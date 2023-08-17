/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:08:05 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/17 11:46:37 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (!s1 || !s2)
		return (-1);
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	i = 0;
	while ((p1[i] != '\0' || p2[i] != '\0') && (i < n))
	{
		if (p1[i] > p2[i])
			return (1);
		else if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (!s1 || !s2)
		return (-1);
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	i = 0;
	while (p1[i] != '\0' || p2[i] != '\0')
	{
		if (p1[i] > p2[i])
			return (1);
		else if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	if (p1[i] > p2[i])
		return (1);
	else if (p1[i] < p2[i])
		return (-1);
	return (0);
}

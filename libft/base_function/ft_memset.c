/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:13:43 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/08 14:50:16 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char				*pt;
	size_t				i;

	pt = str;
	i = 0 ;
	while (i < n)
	{
		pt[i] = c;
		i++;
	}
	return (str);
}

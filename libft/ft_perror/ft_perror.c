/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:34:47 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/17 18:18:19 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_charinstring(char c, char *string)
{
	int		i;
	bool	found;

	if (!string)
		return (false);
	found = false;
	i = 0;
	while (string[i])
	{
		if (string[i] == c)
		{
			found = true;
			break ;
		}
		i++;
	}
	return (found);
}

void	ft_perror(char *string, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, string);
	i = 0;
	while (string[i])
	{
		if (string[i] == '%' && ft_charinstring(string[i + 1], "sd"))
		{
			i++;
			if (string[i] == 's')
				ft_putstr_fd(va_arg(ap, char *), 2);
			if (string[i] == 'd')
				ft_putnbr_fd(va_arg(ap, int), 2);
		}
		else
			ft_putchar_fd(string[i], 2);
		i++;
	}
	va_end(ap);
}

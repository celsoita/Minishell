/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:31:59 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 20:34:11 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_clrs	ft_colors(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		color[i] = ft_toupper(color[i]);
		i++;
	}
	if (!ft_strncmp(color, "GRAY", 4))
		return (GRAY);
	if (!ft_strncmp(color, "RED", 3))
		return (RED);
	if (!ft_strncmp(color, "GREEN", 5))
		return (GREEN);
	if (!ft_strncmp(color, "YELLOW", 6))
		return (YELLOW);
	if (!ft_strncmp(color, "BLUE", 4))
		return (BLUE);
	if (!ft_strncmp(color, "PURPLE", 6))
		return (PURPLE);
	if (!ft_strncmp(color, "CYAN", 4))
		return (CYAN);
	if (!ft_strncmp(color, "WHITE", 5))
		return (WHITE);
	return (DEFAULT);
}

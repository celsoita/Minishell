/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:54:03 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 14:43:21 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void **mem)
{
	if (*mem)
		free(*mem);
	*mem = NULL;
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = ft_strlen_matrix(matrix);
	while(i-- > 0)
	{
		ft_free((void **)&matrix[i]);
	}
	ft_free((void **)&matrix);
}
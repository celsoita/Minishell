/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:54:03 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/18 17:47:09 by cschiavo         ###   ########.fr       */
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

void	ft_free_matrix_len(char **matrix, int len)
{
	int	i;

	if (!matrix)
		return ;
	i = len;
	while(i-- > 0)
		ft_free((void **)&matrix[i]);
	ft_free((void **)&matrix);
}

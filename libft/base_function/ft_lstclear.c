/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:26:24 by cschiavo          #+#    #+#             */
/*   Updated: 2023/08/08 14:45:27 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*st;

	while (*lst)
	{	
		st = ((*lst)->next);
		ft_lstdelone((*lst), del);
		(*lst) = st;
	}
}

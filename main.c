/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:10:15 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/28 20:14:41 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *input;

	env =0;
	input = argv[1];
	argc = 0;
	while (1)
	{
		ft_create_prompt_username();
		input = readline("");
		if (!strcmp(input, "exit"))
		{
			free(input);
			return (1);
		}
		if (input[0])
			add_history(input);
		
	}
	return (0);
}
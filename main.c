/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:32 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/26 19:56:44 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char **argv)
{
	argc = 0;
	char *input;
   	char res[1024];

	input = argv[1];
	while(1)
	{
		input = readline("n");
		if (!strcmp(input, "exit"))
		{
			free(input);
			break ;
		}
		if (!strcmp(input,"pwd"))
		{
			if (getcwd(res, sizeof(res)) != NULL)
				printf("%s\n", res);
			free(input);
		}
		if (input[0])
			add_history(input);
	}
	// printf("NOOO MA PERCHE' SEI USCITO/A\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:07:16 by cschiavo          #+#    #+#             */
/*   Updated: 2023/07/27 18:06:09 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//echo -n ciao>file mondo  "banana al cioccolato"
/*
allora come prima cosa devo contare quante colonne devo allocare,
vorrei procedere scegliendo come carattere separatore lo spazio, 
mettendo dopo ogni spazio la stringa in una matrice, i primi 2 argomenti ,
ovvero le prime 2 stringhe dovrebbero essere il comando e la flag.
dopo salto tutti gli spazi scrivendone solo uno per prendere la stringa
successiva, se trovi " prendi tutti quello dentro e mettilo in una stringa 
compreso le " quindi a regola dopo questa funzione dovremmo avere come res

matrix[0] = echo
matrix[1] = -1
matrix[2] = ciao
matrix[3] = mondo
matrix[4] = "banana al cioccolato"

*/
int	ft_count_input(char *input)
{
	int i;

	i = 0;

	while(input[i] == ' ')
		i++;
	while(input[i] != ' ' &&  input[i] != '\0')
	{
		if (input[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}
// char **ft_main_clean_input(char *input)
// {
// 	int	i;

	

// }
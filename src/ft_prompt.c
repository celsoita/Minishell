/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschiavo <cschiavo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:24:48 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/09/13 01:06:13 by cschiavo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_input(char *prompt)
{
	char	*input;

	input = NULL;
	while (!input || input[0] == '\0')
	{
		free(input);
		input = readline(prompt);
		if (!input)
		{
			printf("\n");
			free(prompt);
			return (input);
		}
	}
	free(prompt);
	return (input);
}

void	ft_create_hostname(t_prompt *prompt)
{
	char	*raw_hostname;
	int		fd;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	raw_hostname = get_next_line(fd);
	close(fd);
	prompt->hostname = malloc(sizeof(char) * ft_strlen(raw_hostname));
	i = -1;
	while (raw_hostname[++i] != '\n')
		prompt->hostname[i] = raw_hostname[i];
	prompt->hostname[i] = '\0';
	free(raw_hostname);
}

void	ft_create_prompt_color(t_prompt *prompt)
{
	char	*temp;

	if (ft_strncmp(prompt->color, "0", 2))
	{
		temp = ft_strjoin("\e[1;", prompt->color);
		free(prompt->color);
		prompt->color = ft_strjoin(temp, "m");
		free(temp);
		temp = prompt->hostname;
		prompt->hostname = ft_strjoin("\e[0m@", temp);
	}
	else
	{
		free(prompt->color);
		prompt->color = malloc(1);
		prompt->color[0] = 0;
		temp = prompt->hostname;
		prompt->hostname = ft_strjoin("@", temp);
	}
	free(temp);
}

char	*ft_create_prompt_username(t_prompt *prompt)
{
	char	*completed_prompt;
	char	*temp;

	if (!prompt->color)
		prompt->color = ft_itoa(DEFAULT);
	ft_create_prompt_color(prompt);
	temp = ft_strjoin(prompt->color, prompt->username);
	free(prompt->color);
	free(prompt->username);
	prompt->username = ft_strjoin(temp, prompt->hostname);
	free(temp);
	free(prompt->hostname);
	completed_prompt = ft_strjoin(prompt->username, ": ");
	free(prompt->username);
	free(prompt);
	return (completed_prompt);
}

char	*ft_create_prompt(t_lexer *lex, char *color)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!color)
		color = ft_itoa(DEFAULT);
	else
		color = ft_itoa(ft_colors(color));
	prompt->color = color;
	prompt->username = ft_expander(lex, "USER");
	if (!prompt->username)
	{
		prompt->username = malloc(1);
		prompt->username[0] = '\0';
	}
	ft_create_hostname(prompt);
	return (ft_create_prompt_username(prompt));
}

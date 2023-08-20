/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CUOGL'attim <CUOGL'attim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:24:48 by CUOGL'attim       #+#    #+#             */
/*   Updated: 2023/08/20 10:10:23 by CUOGL'attim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_colors	ft_colors(char *color)
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

void	ft_create_hostname(t_prompt *prompt)
{
	char	*raw_hostname;
	char	*line;
	int		fd;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	raw_hostname = get_next_line(fd);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	i = 0;
	while (raw_hostname[i] != '.')
		i++;
	prompt->hostname = malloc(sizeof(char) * i + 1);
	i = 0;
	while (raw_hostname[i] != '.')
	{
		prompt->hostname[i] = raw_hostname[i];
		i++;
	}
	prompt->hostname[i] = '\0';
	free(raw_hostname);
}

char	*ft_create_prompt_username(t_prompt *prompt)
{
	char	*completed_prompt;
	char	*temp;

	if (!prompt->color)
		prompt->color = ft_itoa(DEFAULT);
	if (ft_strncmp(prompt->color, "0", 2))
	{
		temp = ft_strjoin("\e[1;", prompt->color);
		free(prompt->color);
		prompt->color = ft_strjoin(temp, "m");
		free(temp);
		temp = prompt->hostname;
		prompt->hostname = ft_strjoin("\e[0m@", temp);
		free(temp);
	}
	else
	{
		free(prompt->color);
		prompt->color = malloc(1);
		prompt->color[0] = 0;
		temp = prompt->hostname;
		prompt->hostname = ft_strjoin("@", temp);
		free(temp);
	}
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

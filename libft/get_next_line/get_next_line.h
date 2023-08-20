/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famirant <famirant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:09:00 by famirant          #+#    #+#             */
/*   Updated: 2023/05/07 21:16:18 by famirant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

// Libraries
# include "../fts_libft/libft.h"

// Functions
char	*get_next_line(int fd);
char	*ft_read_line(int fd, char *lline);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_get_line(char *lline);
char	*ft_new_line(char *lline);

#endif

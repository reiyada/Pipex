/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:26:56 by ryada             #+#    #+#             */
/*   Updated: 2024/11/28 12:46:23 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# if BUFFEER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# elif BUFFER_SIZE > 8000000
#  undef BUFFER_SIZE
#  define BUFFEER_SIZE 8000000
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_read_and_update_remainder(int fd, char *remainder, char *buffer);
char	*ft_extract_line_from_remainder(char **remainder);
char	*ft_finalize_line(char **remainder, char *buffer);

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:26:50 by ryada             #+#    #+#             */
/*   Updated: 2024/11/28 12:58:23 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_update_remainder(int fd, char *remainder, char *buffer)
{
	int		bytes_read;
	char	*temp;

	temp = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
			return (free(remainder), NULL);
		free(remainder);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);
}

char	*ft_extract_line_from_remainder(char **remainder)
{
	char	*line;
	char	*newline_ptr;
	char	*temp;
	size_t	line_length;

	newline_ptr = ft_strchr(*remainder, '\n');
	if (!newline_ptr)
		return (NULL);
	line_length = newline_ptr - *remainder + 1;
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *remainder, line_length + 1);
	temp = ft_strdup(newline_ptr + 1);
	if (!temp)
		return (free(line), NULL);
	free(*remainder);
	*remainder = temp;
	if ((*remainder)[0] == '\0')
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*ft_finalize_line(char **remainder, char *buffer)
{
	char	*line;

	if (*remainder && **remainder)
	{
		line = ft_strdup(*remainder);
		if (!line)
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		line = NULL;
	free(*remainder);
	*remainder = NULL;
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!remainder)
	{
		remainder = ft_strdup("");
		if (!remainder)
			return (free(buffer), NULL);
	}
	remainder = ft_read_and_update_remainder(fd, remainder, buffer);
	if (!remainder)
		return (free(buffer), NULL);
	line = ft_extract_line_from_remainder(&remainder);
	if (line)
		return (free(buffer), line);
	return (ft_finalize_line(&remainder, buffer));
}

// int main(int argc, char **argv)
// {
// 	char *line;
// 	int fd;
// 	int i;

// 	i = 1;
// 	if (argc > 1)
// 	{
// 		fd = open(argv[1],O_RDONLY);
// 		if (fd < 0)
// 		{
// 			perror("Error opening file\n");
// 			return (1);
// 		}
// 		line = get_next_line(fd);
// 		while (line)
// 		{
// 			printf("LINE %d:%s", i, line);
// 			free(line);
// 			i++;
// 			line = get_next_line(fd);
// 		}
// 		close(fd);
// 	}
// 	else
// 	{
// 		perror("Incorrect argument amount\n");
// 		return (1);
// 	}
// 	return (0);
// }

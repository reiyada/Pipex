/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:26:41 by ryada             #+#    #+#             */
/*   Updated: 2024/11/28 08:26:46 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	target;
	int				i;

	target = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == target)
			return ((char *)&s[i]);
		i++;
	}
	if (target == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	if (s1)
		ft_strlcpy(result, s1, len1 + 1);
	if (s2)
		ft_strlcpy(result + len1, s2, len2 + 1);
	return (result);
}

char	*ft_strdup(const char *src)
{
	size_t	length;
	char	*dup;
	size_t	i;

	length = ft_strlen(src) + 1;
	dup = (char *)malloc(sizeof(char) * length);
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dest_size == 0)
		return (src_len);
	if (dest_size > 0)
	{
		i = 0;
		while (i < dest_size -1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

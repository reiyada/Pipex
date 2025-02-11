/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:46:47 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:28:27 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		target;
	size_t				i;

	ptr = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == target)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     char src[] = "Hello world";
//     char search = 'o';
//     size_t i = sizeof(src);
//     char *result = ft_memchr(src, search, i);
//     if (result != NULL)
//         printf("Found '%c' at position %ld\n", search, result - src);
//     else
//         printf("Character '%c' not found\n", search);
//     return (0);
// }
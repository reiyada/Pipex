/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:47:14 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:32:09 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
//     const char str1[] = "Hello";
//     const char str2[] = "Hello world";
//     size_t j = 7;
//     int result = ft_strncmp(str1, str2, j);
//     if (result == 0)
//         printf("The first 7 characters are the same.\n");
//     else
//         printf("The first 7 characters are not the same.\n");
//     return (0);
// }
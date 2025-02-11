/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:47:43 by ryada             #+#    #+#             */
/*   Updated: 2024/11/07 09:29:31 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     const char src[] = "hello world wowo";
//     const char find[] = "world";
//     size_t findsize = 10;
//     char *result = ft_strnstr(src, find, findsize);
//     if (result != NULL)
//         printf("Substring '%s' found at position: %s\n", find, result);
//     else
//         printf("Substring '%s' not found.\n", find);
//     return (0);
// }
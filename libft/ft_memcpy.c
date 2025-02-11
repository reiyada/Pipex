/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:47:50 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 12:04:18 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*byte_dest;
	unsigned char	*byte_src;

	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	byte_dest = (unsigned char *)dest;
	byte_src = (unsigned char *)src;
	while (n > 0)
	{
		*byte_dest = *byte_src;
		byte_dest++;
		byte_src++;
		n--;
	}
	return (dest);
}

// int main(void)
// {
//     char dest_1[6];
//     const char src_1[6] = "Hello";
//     ft_memcpy(dest_1, src_1, 5);
//     dest_1[5] = '\0';
//     printf("%s\n", dest_1);
//     return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:12:36 by ryada             #+#    #+#             */
/*   Updated: 2024/12/31 13:06:12 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	byte_dest = (unsigned char *)dest;
	byte_src = (const unsigned char *)src;
	if (byte_dest > byte_src && byte_dest < byte_src + n)
	{
		byte_dest += n;
		byte_src += n;
		while (n--)
			*(--byte_dest) = *(--byte_src);
	}
	else
	{
		while (n--)
			*(byte_dest++) = *(byte_src++);
	}
	return (dest);
}
// int main(void)
// {
//     const char src1[] = "Hello World!";
//     char dest1[20];
//     printf("Original src1 : %s\n", src1);
//     ft_memmove(dest1, src1, ft_strlen(src1) + 1);
//     printf("Non-over lapping dest1 after memmove : %s\n", dest1);
//     char src2[] = "Overlap case test";
//     printf("Original src2 : %s\n", src2);
//     ft_memmove(src2 + 0, src2 + 8, 9);
//     printf("Overlapping src2 after memmove: %s\n", src2);

//     const char src3[] = "Edge case";
//     char dest3[20] = "Original";
//     ft_memmove(dest3, src3, 0); 
//     printf("Dest3 after 0-byte memmove: %s\n", dest3);
//     return (0);
// }

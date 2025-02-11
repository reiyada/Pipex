/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:24:46 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 15:00:50 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// int main(void)
// {
// 	char src1[] = "Hello World";
// 	char dest1[12];
// 	printf("Original of dest1 : %s\n", dest1);
// 	size_t src1_size = ft_strlcpy(dest1, src1, 12);
// 	printf("After the copy : %s\n", dest1);
// 	printf("The size of src1 : %ld\n", src1_size);
// 	return (0);
// }
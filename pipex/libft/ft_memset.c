/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:29:50 by ryada             #+#    #+#             */
/*   Updated: 2024/11/05 13:18:08 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte_ptr;
	unsigned char	byte_value;

	byte_ptr = (unsigned char *)ptr;
	byte_value = (unsigned char)value;
	while (num > 0)
	{
		*byte_ptr = byte_value;
		byte_ptr++;
		num--;
	}
	return (ptr);
}

// int main()
// {
//     char buffer[10];
//     int i;

//     i = 0;
//     ft_memset(buffer, 'A', sizeof(buffer));
//     while (i < sizeof(buffer))
//     {
//         printf("%c\n", buffer[i]);
//         i++;
//     }
//     return (0);
// }
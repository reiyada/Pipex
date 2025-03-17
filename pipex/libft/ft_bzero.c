/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:05:19 by ryada             #+#    #+#             */
/*   Updated: 2024/11/05 13:13:25 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t num)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)ptr;
	while (num > 0)
	{
		*byte_ptr = 0;
		byte_ptr++;
		num--;
	}
}

// int main(void)
// {
//     char ptr_1[10] = "HelloWorld";
//     ft_bzero(ptr_1, 5);
//     int i;

//     i = 0;
//     while (i < 10)
//     {
//         if (ptr_1[i] == '\0')
//             printf("\\0");
//         else
//             printf("%c", ptr_1[i]);
//         i++;
//     }
//     printf("\n");
//     return (0);
// }
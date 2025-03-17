/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:06:56 by ryada             #+#    #+#             */
/*   Updated: 2024/11/07 13:37:49 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

// int main(void)
// {
// 	int *array;
// 	size_t n = 5;
// 	size_t i = 0;
// 	array = (int *)ft_calloc(n, sizeof(int));
// 	if (!array)
// 	{
// 		printf("The allocation failed");
// 		return (1);
// 	}
// 	printf("Allocated array with ft_calloc is:");
// 	while (i < n)
// 	{
// 		printf ("%d", array[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(array);
// 	return (0);
// }
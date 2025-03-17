/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:37:30 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 14:01:57 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	result;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	result = (n % 10) + '0';
	write (fd, &result, 1);
}

// int main()
// {
//     int nb = 123;
//     int fd = 1;
//     ft_putnbr_fd(nb, fd);
//     return (0);
// }
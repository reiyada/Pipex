/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:47:18 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:33:38 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == (char)c)
			return ((char *)&s[len]);
		len--;
	}
	if (s[0] == (char)c)
		return ((char *)&s[0]);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	return (NULL);
}

// int main() 
// {
//     const char *str = "hello world";
//     char ch = 'o';

//     char *position = ft_strrchr(str, ch);

//     if (position == NULL) 
//         printf("Character '%c' not found in the string \"%s\".\n", ch, str);
//     else 
//         printf("Character '%c' found at <<%ld>>.\n", ch, position - str);

//     return 0;
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:11:49 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 14:58:01 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countword(char const *str, char sp)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sp)
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != '\0' && str[i] != sp)
				i++;
		}
	}
	return (count);
}

void	ft_free_all_alloc(char **table, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free (table[i]);
		i++;
	}
	free(table);
}

size_t	ft_skip_sep(const char *s, char c, size_t index)
{
	while (s[index] == c)
		index++;
	return (index);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	start;
	size_t	end;
	int		i;

	start = 0;
	i = 0;
	result = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[start])
	{
		start = ft_skip_sep(s, c, start);
		if (s[start] == '\0')
			break ;
		end = start;
		while (s[end] != c && s[end])
			end++;
		result[i] = ft_substr(s, start, end - start);
		if (!result[i])
			return (ft_free_all_alloc(result, i), NULL);
		start = end;
		i++;
	}
	return (result[i] = NULL, result);
}
// int main()
// {
//     char const str[] = "Hello I am Rei";
//     char sep = ' ';
//     char **result = ft_split(str, sep);
//     int i = 0;
//     while (result[i])
//     {
//         printf("%s\n", result[i]);
//         i++;
//     }
//     return (0);
// }

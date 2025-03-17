/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:38:14 by ryada             #+#    #+#             */
/*   Updated: 2024/11/12 09:38:38 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int main()
// {
//     int value = 42;
//     t_list *node;
//     node = ft_lstnew(&value);
//     if(node)
//     {
//         printf("Node content: %d\n",*(int *)(node->content));
//         free(node);
//     }
//     return (0);
// }
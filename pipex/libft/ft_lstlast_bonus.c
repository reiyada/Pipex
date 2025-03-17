/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:20:47 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:37:03 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

// t_list *ft_create_node(void *value)
// {
//     t_list *node;

//     node = (t_list *)malloc(sizeof(t_list));
//     if (!node)
//         return NULL;
//     node->content = value;
//     node->next = NULL;
//     return node;
// }

// int main()
// {
//     t_list *head = ft_create_node("NODE 1");
//     head->next = ft_create_node("NODE 2");
//     head->next->next = ft_create_node("NODE 3");
//     t_list *last = ft_lstlast(head);
//     printf("The last node of the list : %s\n", (char *)last->content);
//     t_list *temp;
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
//     return 0;
// }
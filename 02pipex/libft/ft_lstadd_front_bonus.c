/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:20:35 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:35:35 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
//     t_list *newnode = ft_create_node("NEW NODE");
//     ft_lstadd_front(&head, newnode);
//     t_list *current = head;
//     int i = 1;
//     while (current)
//     {
//         printf("%d : %s\n", i, (char *)current->content);
//         current = current->next;
//         i++;
//     }
//     t_list *temp;
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
//     return 0;
// }
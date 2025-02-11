/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:20:55 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:36:04 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
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
//     int num = ft_lstsize(head);
//     printf("The number of the list is %d\n", num);
//     t_list *temp;
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
//     return 0;
// }
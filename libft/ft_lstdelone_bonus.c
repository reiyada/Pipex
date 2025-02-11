/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:20:41 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:38:33 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
// void delete_content(void *content)
// {
//     free(content);
// }

// t_list *create_node(const char *str)
// {
//     int i = 0;
//     while (str[i])
//         i++;
//     char *content = malloc(sizeof(char) * (i + 1));
//     if (!content)
//         return NULL;
//     i = 0;
//     while (str[i])
//     {
//         content[i] = str[i];
//         i++;
//     }
//     content[i] = '\0';
//     return ft_lstnew(content);
// }

// int main(void)
// {
//     t_list *list = create_node("Node 1");
//     list->next = create_node("Node 2");
//     list->next->next = create_node("Node 3");
//     printf("List before ft_lstdelone:\n");
//     t_list *temp = list;
//     while (temp)
//     {
//         printf("%s\n", (char *)temp->content);
//         temp = temp->next;
//     }
//     t_list *new_head = list->next;
//     ft_lstdelone(list, delete_content);
//     list = new_head;

//     printf("List after ft_lstdelone:\n");
//     temp = list;
//     while (temp)
//     {
//         printf("%s\n", (char *)temp->content);
//         temp = temp->next;
//     }
//     while (list)
//     {
//         temp = list->next;
//         ft_lstdelone(list, delete_content);
//         list = temp;
//     }
//     return 0;
// }

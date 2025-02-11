/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:20:44 by ryada             #+#    #+#             */
/*   Updated: 2024/11/14 10:40:06 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

// void to_uppercase(void *content)
// {
//     char *str = (char *)content;
//     while (*str)
//     {
//         if (*str >= 'a' && *str <= 'z')
//             *str -= 32;
//         str++;
//     }
// }
// void print_content(void *content)
// {
//     printf("%s\n", (char *)content);
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
//     t_list *list = create_node("I");
//     list->next = create_node("am");
//     list->next->next = create_node("Rei");
//     t_list *temp = list;

//     printf("List content before modifying:\n");
//     ft_lstiter(temp, print_content);

//     ft_lstiter(temp, to_uppercase);
//     printf("List content after converting to uppercase:\n");
//     ft_lstiter(list, print_content);

//     t_list *clear;
//     while (list)
//     {
//         clear = list;
//         list = list->next;
//         free(clear);
//     }
//     return 0;
// }

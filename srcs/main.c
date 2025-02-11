/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/11 16:44:19 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int mian(int argc, char **argv)
{
    int fd_in;
    int fd_out;
    if (argc != 5)
        return(ft_putstr_fd("Error\n", 2), 1);
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)
        return(ft_putstr_fd("Error\n", 2), 1);
    fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
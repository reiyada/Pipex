/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/12 17:48:14 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int mian(int argc, char **argv)
{
    int fd_in;
    int fd_out;
    int pipefd[2];
    int pid1;
    int pid2;
    if (argc != 5)
        return(perror("Error\n"), 1);
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)//read fail on input
        return(perror("Error\n"), 1);
    fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);//write, create(if not exist), empty(if it exist), permission to write and read for the owner
    if (fd_out < 0)// read fail on outpt
        return(perror("Error\n"), 1);
    if (pipe(pipefd) == -1)
        return (perror("Error\n"), 1);
    pid1 = fork();
    if (pid1 == 0)
    {
        
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/12 22:20:06 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// int mian(int argc, char **argv)
// {
//     int fd_in;
//     int fd_out;
//     int pipefd[2];
//     int pid1;
//     int pid2;
//     if (argc != 5)
//         return(perror("Error\n"), 1);
//     fd_in = open(argv[1], O_RDONLY);//read infile
//     if (fd_in < 0)//read fail on input
//         return(perror("Error\n"), 1);
//     fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);//write, create(if not exist), empty(if it exist), permission to write and read for the owner
//     if (fd_out < 0)// read fail on outpt
//         return(perror("Error\n"), 1);
//     if (pipe(pipefd) == -1)
//         return (perror("Error\n"), 1);
//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         dup2()
//     }
// }

int main(int argc, char **argv, char **env)
{
    int pipe_fd[2];
    pid_t pid;

    if (argc != 5)
        return(prror("Incorrect argument number!\n"), 1);
    if (pipe(pipe_fd) == -1)
        return(perror("Pipe creation failed!\n"), 1);
    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed!\n");
        exit(1);
    }
    else if (pid == 0)//child
    {
        ft_child
    }
    else//parent
    {
        ft_parent
    }
}
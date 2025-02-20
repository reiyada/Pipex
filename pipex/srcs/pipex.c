/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/20 17:24:30 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_exec(char *cmd, char **envp)
{
    char **cmd_tab;
    char *cmd_path;

    cmd_tab = ft_split(cmd, ' ');//(ex) "ls -l" -> cmd_tab[0] = "ls", cmd_tab[1] = "-l"
    cmd_path = ft_get_path(cmd_tab[0], envp);//(ex) "ls -l" -> find the enviromental path of "ls" -> /bin/ls
    if (!cmd_path)//if there is no path
    {
        ft_putstr_fd("[Error] Commnd not found! : ", 2);
        ft_putendl_fd(cmd_tab[0], 2);
        ft_free_tab(cmd_tab);
        exit(127);
    }
    if (execve(cmd_path, cmd_tab, envp) == -1)// execute the command, and if it fails,
    {
        ft_putstr_fd("[Error] Commnd execution failed!: ", 2);
        ft_putendl_fd(cmd_tab[0], 2);
        ft_free_tab(cmd_tab);
        exit(1);
    }
    ft_free_tab(cmd_tab);
}

void ft_first_child(char **argv, int *pipe_fd, char **envp)
{
    int fd;

    fd = open(argv[1], O_RDONLY | O_CREAT, 0777);//open the infile and read, create if it doesnt exist
    if (fd < 0)
    {
        ft_putstr_fd("[Error] Opening the input file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
    dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
    close(pipe_fd[0]);//close the pipe(read) because we dont need it
    ft_exec(argv[2], envp);//execute the first command
}

void ft_second_child(char **argv, int *pipe_fd, char **envp)
{
    int fd;

    fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);//open the outfile and write, create if it doesnt exist, empty it if it exists already
    if (fd < 0)
    {
        ft_putstr_fd("[Error] Opening the input file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);//set argv[4] as the output of the parent process
    dup2(pipe_fd[0], STDIN_FILENO);//set the pipe(read) as the input of the parent process
    close(pipe_fd[1]);//close the pipe(write) because we dont need it
    ft_exec(argv[3], envp);//execute the second command
}

int main(int argc, char **argv, char **envp)
{
    int status;
    int pipe_fd[2];
    pid_t pid1;
    pid_t pid2;

    if (argc != 5)
        return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
    if (!ft_check_argv(argv))
        return (ft_putstr_fd("[Error] Invalid argument!\n", 2), 1);
    if (pipe(pipe_fd) == -1)
        return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
    pid1 = fork();
    if (pid1 == -1)
        return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
    if (pid1 == 0) // First child executes cmd1
        ft_first_child(argv, pipe_fd, envp);
    waitpid(pid1, &status, 0);
    close(pipe_fd[1]); // Parent closes write end of pipe
    pid2 = fork(); // Fork again for the sond commanecd
    if (pid2 == -1)
        return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
    if (pid2 == 0) // Second child executes cmd2
        ft_second_child(argv, pipe_fd, envp);
    close(pipe_fd[0]); // Parent closes read end of pipe
    waitpid(pid1, &status, 0); // Wait for cmd1
    waitpid(pid2, &status, 0); // Wait for cmd2
    return (WEXITSTATUS(status)); // Return the exit status of cmd2 (last command)
}


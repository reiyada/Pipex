/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/13 17:36:14 by ryada            ###   ########.fr       */
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

// each cmd needs a stdin (input) and returns an output (to stdout)
//     infile                                             outfile
// as stdin for cmd1                                 as stdout for cmd2            
//        |                        PIPE                        ↑
//        |           |---------------------------|            |
//        ↓             |                       |              |
//       cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
//                      |                       |
//             cmd1   |---------------------------|  end[0]
//            output                             reads end[1]
//          is written                          and sends cmd1
//           to end[1]                          output to cmd2
//        (end[1] becomes                      (end[0] becomes 
//         cmd1 stdout)                           cmd2 stdin)

void ft_exec(char *cmd, char **envp)
{
    char **cmd_tab;
    char *cmd_path;

    //printf("DEBUG: command %s\n", cmd);
    cmd_tab = ft_split(cmd, ' ');
    cmd_path = ft_get_path(cmd_tab[0], envp);
    if (!cmd_path)
    {
        ft_putstr_fd("Command path not found!\n", 2);
        ft_free_tab(cmd_tab);
        exit(127);
    }
    //printf("DEBUG: Executing %s\n", cmd_tab[0]); 
    if (execve(cmd_path, cmd_tab, envp) == -1)//if execution fails
    {
        ft_putstr_fd("Command not found: ", 2);
        ft_putendl_fd(cmd_tab[0], 2);
        ft_free_tab(cmd_tab);
        exit(1);
    }
    ft_free_tab(cmd_tab);
}

// void ft_exec(char *cmd, char *arg, char **envp)
// {
//     char **cmd_tab;
//     char *cmd_path;
//     char *full_cmd;

//     // If the argument is not NULL, concatenate command and argument
//     if (arg && *arg != '\0')
//     {
//         full_cmd = ft_strjoin(cmd, " "); // Add a space between cmd and arg
//         full_cmd = ft_strjoin(full_cmd, arg); // Append arg
//     }
//     else
//         full_cmd = cmd; // No argument, use command directly

//     printf("DEBUG: Received command: [%s]\n", full_cmd);

//     cmd_tab = ft_split(full_cmd, ' '); // Split command into arguments
//     if (!cmd_tab || !cmd_tab[0])
//     {
//         perror("Error: Command parsing failed");
//         exit(127);
//     }

//     printf("DEBUG: Parsed command: [%s]\n", cmd_tab[0]);

//     cmd_path = ft_get_path(cmd_tab[0], envp);
//     if (!cmd_path)
//     {
//         perror("Command not found!");
//         exit(127);
//     }

//     printf("DEBUG: Executing %s\n", cmd_path);

//     if (execve(cmd_path, cmd_tab, envp) == -1)
//     {
//         perror("Execution failed!");
//         exit(1);
//     }
// }


void ft_child(char **argv, int *pipe_fd, char **envp)
{
    
    int fd;

    fd = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        ft_putstr_fd("Opening the input file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDIN_FILENO);//argv[1] will be the input of the child process
    dup2(pipe_fd[1], STDOUT_FILENO);//the output of the child process will be in pipe_fd[1]
    close(pipe_fd[0]);//close bc this is not needed
    //printf("DEBUG: calling the child\n");
    ft_exec(argv[2], envp);
}

void ft_parent(char **argv, int *pipe_fd, char **envp)
{
    
    int fd;

    fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        ft_putstr_fd("Opening the input file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);//argv[4] will be the output of the parent process
    dup2(pipe_fd[0], STDIN_FILENO);//pipe_fd[0] reads pipe_fd[1] and becomes input of the parent process
    close(pipe_fd[1]);//close bc this is not needed
    //printf("DEBUG: calling the parent\n");
    ft_exec(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
    int status;
    int pipe_fd[2];
    pid_t pid;

    if (argc != 5)
        return(perror("Incorrect argument number!\n"), 1);
    if (!ft_check_argv(argv))
        return(perror("Invalid argument!\n"), 1);
    // if (!ft_check_cmd(argv, envp))
    //     return(perror("Command not found!\n"), 1);
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
        ft_child(argv, pipe_fd, envp);
    }
    else
    {
        waitpid(pid, &status, 0);
        
        ft_parent(argv, pipe_fd, envp);
        if (WEXITSTATUS(status) == 127)
            return(perror("Command not found!\n"), 0);     
    }
    return (0);
}

// int main(int argc, char **argv, char **envp)
// {
//     char *path = ft_get_path(argv[2], envp);
    
//     if (argc != 5)
//         return(perror("Incorrect argument number!\n"), 1);
//     printf("command : %s\n", argv[2]);
//     if (path)
//         printf("Found PATH: %s\n", path);
//     else
//         printf("ERROR: PATH variable not found!\n");

//     return 0;
// }
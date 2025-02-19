/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/19 13:18:38 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
void ft_one_child(char **argv, char **envp)
{
    int fd_read;
    int fd_write;

    fd_read = open(argv[1], O_RDONLY | O_CREAT, 0777);//open the infile and read, create if it doesnt exist
    if (fd_read < 0)
    {
        ft_putstr_fd("[Error] Opening the input file failed!\n", 2);
        exit(1);
    }
    fd_write = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);//open the outfile and write, create if it doesnt exist, empty it if it exists already
    dup2(fd_read, STDIN_FILENO);//set argv[1] as the input of the child process
    dup2(fd_write, STDOUT_FILENO);//set agrgv[3] as the output of the child process
    ft_exec(argv[2], envp);//execute the first command
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

// void ft_middle_child(char *argv, int *pipe_fd, char **envp)
// {
//     dup2(pipe_fd[0], STDIN_FILENO);//set argv[1] as the input of the child process
//     dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
//     ft_exec(argv, envp);//execute the first command
// }

void ft_middle_child(char **argv, int *pipe_fd, char **envp, int i, int num_cmds)
{
    int j;

    dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO);
    dup2(pipe_fd[i * 2 + 1], STDOUT_FILENO);
    j = 0;
    while (j < (2 * (num_cmds - 1)))
    {
        close(pipe_fd[j]);
        j++;
    }
    ft_exec(argv[i + 2], envp);
}

void ft_last_child(int argc, char **argv, int *pipe_fd, char **envp)
{
    int fd;
    int last;

    last = argc - 1;
    fd = open(argv[last], O_WRONLY | O_CREAT | O_TRUNC, 0777);//open the outfile and write, create if it doesnt exist, empty it if it exists already
    if (fd < 0)
    {
        ft_putstr_fd("[Error] Opening the input file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);//set argv[last] as the output of the process
    dup2(pipe_fd[0], STDIN_FILENO);//set the pipe(read) as the input of the process
    close(pipe_fd[1]);//close the pipe(write) because we dont need it
    ft_exec(argv[last - 1], envp);//execute the second command
}

void    ft_here_doc(char *limiter, int argc)
{
    pid_t reader;
    int pipe_fd[2];
    char *line;
    
    if (argc < 6)
        return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2));
    if (pipe(pipe_fd) == -1)
        return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2));
    reader = fork();
    if (reader == -1)
        return (ft_putstr_fd("[Error] Fork failed!\n", 2));
    if (reader == 0)//child
    {
        close(pipe_fd[0]);
        while((line = get_next_line(0)))
        {
            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
            {
                free (line);
                break;
            }
            write(pipe_fd[1], line, ft_strlen(line));
            free(line);
        }
        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        waitpid(reader, NULL, 0);
    }
}

void ft_first_child_here_doc(char **argv, int *pipe_fd, char **envp)
{
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    ft_exec(argv[3], envp);
}

void ft_last_child_here_doc(int argc, char **argv, int *pipe_fd, char **envp)
{
    int fd;
    int last = argc - 1;

    fd = open(argv[last], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("[Error] Opening the output file failed!\n", 2);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    ft_exec(argv[last - 1], envp);
}



int main(int argc, char **argv, char **envp)
{
    int status;
    int *pipe_fd;
    pid_t *pid;
    int i;
    int num_cmds;
    int here_doc;

    if (argc < 5)
        return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);

    here_doc = 0;

    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        here_doc = 1;
        num_cmds = argc - 4;
    }
    else
    {
        num_cmds = argc - 3;
    }


    pipe_fd = malloc(sizeof(int) * (2 * (num_cmds - 1)));
    pid = malloc(sizeof(pid_t) * num_cmds);
    if (!pipe_fd || !pid)
        return (ft_putstr_fd("[Error] Memory allocation failed!\n", 2), 1);

    if (here_doc)
        ft_here_doc(argv[2], argc); // Call here_doc function

    i = 0;
    while (i < num_cmds - 1)
    {
        if (pipe(pipe_fd + (2 * i)) == -1)
            return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
        i++;
    }

    i = 0;
    while (i < num_cmds)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
        if (pid[i] == 0)
        {
            if (num_cmds == 1)
                ft_one_child(argv, envp);
            else if (i == 0 && here_doc)
                ft_first_child_here_doc(argv, pipe_fd, envp);  // Handle first command after here_doc
            else if (i == 0)
                ft_first_child(argv, pipe_fd, envp);
            else if (i == num_cmds - 1)
                ft_last_child_here_doc(argc, argv, pipe_fd, envp);
            else
                ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
        }
        i++;
    }

    i = 0;
    while (i < 2 * (num_cmds - 1))
    {
        close(pipe_fd[i]);
        i++;
    }
    i = 0;
    while (i < num_cmds)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    free(pipe_fd);
    free(pid);
    return (WEXITSTATUS(status));
}


// int main(int argc, char **argv, char **envp)
// {
//     int status;
//     int *pipe_fd;
//     pid_t *pid;
//     int i;
//     int num_cmds;
//     char *limiter;

//     if (ft_strncmp(argv[1], "here_doc", 8) == 0)
//     {
//         i = 3;
//         //fileout = open_file(argv[argc - 1], 0);
//         ft_here_doc(argv[2], argc);
//     }
//     else
//     {
//         if (argc <= 4)
//             return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
//         num_cmds = argc - 3;
//         pipe_fd = malloc(sizeof(int) * (2 * (num_cmds - 1)));
//         pid = malloc(sizeof(pid_t) * num_cmds);
//         if (!pipe_fd || !pid)
//             return (ft_putstr_fd("[Error] Memory allocation failed!\n", 2), 1);
//         i = 0;
//         while (i < num_cmds - 1)
//         {
//             if (pipe(pipe_fd + (2 * i)) == -1)
//                 return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
//             i++;
//         }
//         i = 0;
//         while (i < num_cmds)
//         {
//             pid[i] = fork();
//             if (pid[i] == -1)
//                 return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
//             if (pid[i] == 0)
//             {
//                 if (num_cmds == 1)
//                     ft_one_child(argv, envp);
//                 else if (i == 0)
//                     ft_first_child(argv, pipe_fd, envp);
//                 else if (i == num_cmds - 1)
//                     ft_last_child(argc, argv, pipe_fd, envp);
//                 else
//                     ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
//             }
//             i++;
//         }
//         i = 0;
//         while (i < 2 * (num_cmds - 1))
//         {
//             close(pipe_fd[i]);
//             i++;
//         }
//         i = 0;
//         while (i < num_cmds)
//         {
//             waitpid(pid[i], &status, 0);
//             i++;
//         }
//         free(pipe_fd);
//         free(pid);
//         return (WEXITSTATUS(status));
//     }
    
// }


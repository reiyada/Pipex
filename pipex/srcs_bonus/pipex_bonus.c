/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/20 17:38:41 by ryada            ###   ########.fr       */
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
// void ft_one_child(char **argv, char **envp)
// {
//     int fd_read;
//     int fd_write;

//     fd_read = open(argv[1], O_RDONLY | O_CREAT, 0777);//open the infile and read, create if it doesnt exist
//     if (fd_read < 0)
//     {
//         ft_putstr_fd("[Error] Opening the input file failed!\n", 2);
//         exit(1);
//     }
//     fd_write = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);//open the outfile and write, create if it doesnt exist, empty it if it exists already
//     dup2(fd_read, STDIN_FILENO);//set argv[1] as the input of the child process
//     dup2(fd_write, STDOUT_FILENO);//set agrgv[3] as the output of the child process
//     ft_exec(argv[2], envp);//execute the first command
// }

void ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc)
{
    int fd;

    if (here_doc)//here_doc
        dup2(pipe_fd[1], STDOUT_FILENO);//pipe(write) is set as stdout
    else//multiple cmds
    {
        fd = ft_open_file(argv[1], 1);
        dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
        close(fd);
        dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
    }
    close(pipe_fd[0]);//close the pipe(read) because we dont need it
    close(pipe_fd[1]);
    if (here_doc)
        ft_exec(argv[3], envp);//execute the first command
    else
        ft_exec(argv[2], envp);//execute the first command
}

void ft_middle_child(char *cmd, char **envp, int *prev_pipe, int *new_pipe)
{
    dup2(prev_pipe[0], STDIN_FILENO); // Read from previous pipe
    dup2(new_pipe[1], STDOUT_FILENO); // Write to new pipe

    close(prev_pipe[0]);
    close(prev_pipe[1]);
    close(new_pipe[0]);
    close(new_pipe[1]);

    ft_exec(cmd, envp);
}

// void ft_middle_child(char **argv, int *pipe_fd, char **envp, int i, int num_cmds)
// {
//     int j;

//     dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO);
//     dup2(pipe_fd[i * 2 + 1], STDOUT_FILENO);
//     j = 0;
//     while (j < (2 * (num_cmds - 1)))
//     {
//         close(pipe_fd[j]);
//         j++;
//     }
//     ft_exec(argv[i + 2], envp);
// }

void ft_last_child(int argc, char **argv, char **envp, int *pipe_fd, int here_doc)
{
    int fd;

    if (here_doc)
        fd = ft_open_file(argv[argc -1], 0);//APPEND
    else
        fd = ft_open_file(argv[argc -1], 1);//NOT APPEND
    dup2(fd, STDOUT_FILENO);//set argv[last] as the output of the process
    dup2(pipe_fd[0], STDIN_FILENO);//set the pipe(read) as the input of the process
    close(fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);//close the pipe(write) because we dont need it
    ft_exec(argv[argc - 2], envp);//execute the last command
}

// void    ft_here_doc(char *limiter, int argc)
// {
//     pid_t reader;
//     int pipe_fd[2];
//     char *line;
    
//     if (argc < 6)
//         return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2));
//     if (pipe(pipe_fd) == -1)//pipe creation between two cmds
//         return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2));
//     reader = fork();
//     if (reader == -1)
//         return (ft_putstr_fd("[Error] Fork failed!\n", 2));
//     if (reader == 0)//child
//     {
//         close(pipe_fd[0]);//close the pipe (read)
//         while((line = get_next_line(0)))//read line by line from the stdin(terminal:0)
//         {
//             if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
//             {
//                 free (line);
//                 break;
//             }
//             write(pipe_fd[1], line, ft_strlen(line));//in the pipe(write), we write one line
//             free(line);//free the line already written
//         }
//         close(pipe_fd[1]);//finish putting output into the pipe(write) by closing it
//         exit(EXIT_SUCCESS);
//     }
//     else//parent: setting all the input/output place
//     {
//         close(pipe_fd[1]);
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[0]);
//         waitpid(reader, NULL, 0);
//     }
// }

void ft_here_doc(char *limiter, int argc)
{
    int pipe_fd[2];
    char *line;

    if (argc < 6)
    {
        ft_putstr_fd("[Error] Incorrect argument number!\n", 2);
        exit(1);
    }
    if (pipe(pipe_fd) == -1)
    {
        ft_putstr_fd("[Error] Pipe creation failed!\n", 2);
        exit(1);
    }
    if (fork() == 0)//child
    {
        close(pipe_fd[0]);//close the pipe(read)
        while((line = get_next_line(0)))
        {
            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
            {
                free (line);
                break;
            }
            write(pipe_fd[1], line, ft_strlen(line));//in the pipe(write), we write one line
            free(line);//free the line already written
        }
        close(pipe_fd[1]);//finish putting output into the pipe(write) by closing it
        exit(EXIT_SUCCESS);
    }
    else//parent: setting all the input/output place
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        wait(NULL);
    }
}

// void ft_first_child_here_doc(char **argv, int *pipe_fd, char **envp)
// {
//     dup2(pipe_fd[1], STDOUT_FILENO);
//     close(pipe_fd[0]);
//     ft_exec(argv[3], envp);
// }

// void ft_second_child_here_doc(int argc, char **argv, int *pipe_fd, char **envp)
// {
//     int fd;
//     int last = argc - 1;

//     fd = open(argv[last], O_WRONLY | O_CREAT | O_APPEND, 0644);
//     if (fd < 0)
//     {
//         ft_putstr_fd("[Error] Opening the output file failed!\n", 2);
//         exit(1);
//     }
//     dup2(fd, STDOUT_FILENO);
//     dup2(pipe_fd[0], STDIN_FILENO);
//     close(pipe_fd[1]);
//     ft_exec(argv[last - 1], envp);
// }


//doesnt work with the multiple cmds, outfile keeps the content inside from the last call
// int main(int argc, char **argv, char **envp)
// {
//     int status;
//     int *pipe_fd;
//     pid_t *pid;
//     int i;
//     int num_cmds;
//     int here_doc;

//     if (argc < 5)
//         return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
//     here_doc = 0;
//     if (ft_strncmp(argv[1], "here_doc", 8) == 0)
//     {
//         here_doc = 1;
//         num_cmds = argc - 4;//./pipex "here_doc" "LIMITTER" "cmd1" "cmd2" "outfile"
//     }
//     else
//         num_cmds = argc - 3;//./pipex "infile" "cmd1" "cmd2" "cmd3" .... "outfile"
//     pipe_fd = malloc(sizeof(int) * (2 * (num_cmds - 1)));
//     pid = malloc(sizeof(pid_t) * num_cmds);
//     if (!pipe_fd || !pid)
//         return (ft_putstr_fd("[Error] Memory allocation failed!\n", 2), 1);
//     if (here_doc)
//         ft_here_doc(argv[2], argc); // Call ft_here_doc function
//     else
//     {
//         i = 0;
//         while (i < num_cmds - 1)
//         {
//             if (pipe(pipe_fd + (2 * i)) == -1)
//                 return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
//             i++;
//         }
//     }
//     i = 0;
//     while (i < num_cmds)
//     {
//         pid[i] = fork();
//         if (pid[i] == -1)
//             return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
//         if (pid[i] == 0)
//         {
//             if (num_cmds == 1)
//                 ft_one_child(argv, envp);
//             else if (i == 0 && here_doc)
//                 ft_first_child_here_doc(argv, pipe_fd, envp);  // Handle first command after here_doc
//             else if (i == 0)
//                 ft_first_child(argv, pipe_fd, envp);
//             else if (i == num_cmds - 1)
//                 ft_last_child_here_doc(argc, argv, pipe_fd, envp);
//             else
//                 ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
//         }
//         i++;
//     }
    
//     i = 0;
//     while (i < 2 * (num_cmds - 1))
//     {
//         close(pipe_fd[i]);
//         i++;
//     }
//     i = 0;
//     while (i < num_cmds)
//     {
//         waitpid(pid[i], &status, 0);
//         i++;
//     }
//     free(pipe_fd);
//     free(pid);
//     return (WEXITSTATUS(status));
// }

int main(int argc, char **argv, char **envp)
{
    int i;
    int is_here_doc = 0;
    int pipe_fds[2];
    int prev_pipe[2];

    if (argc < 5)
        return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);

    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        is_here_doc = 1;
        i = 3; // Start at cmd1 (after "here_doc" and LIMITER)
        ft_here_doc(argv[2], argc); // Handle user input
    }
    else
        i = 2; // Start at cmd1 (after infile)

    while (i < argc - 2)
    {
        if (pipe(pipe_fds) == -1)
            return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);

        if (fork() == 0)
        {
            if ((is_here_doc && i == 3) || (!is_here_doc && i == 2))
                ft_first_child(argv, pipe_fds, envp, is_here_doc);
            else if (i == argc - 3)
                ft_last_child(argc, argv, envp, pipe_fds, is_here_doc);
            else
                ft_middle_child(argv[i], envp, prev_pipe, pipe_fds);
        }

        close(prev_pipe[0]); // Close old pipe read end
        close(prev_pipe[1]); // Close old pipe write end
        prev_pipe[0] = pipe_fds[0]; // Store new pipe as previous pipe
        prev_pipe[1] = pipe_fds[1];

        close(pipe_fds[1]); // Parent closes write end
        dup2(pipe_fds[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipe_fds[0]); // Close read end after redirection
        i++;
    }

    wait(NULL);
    return (0);
}


// int main(int argc, char **argv, char **envp)
// {
//     int filein;
//     int fileout;
//     int pipe_fd[2];
//     int i;
//     int here_doc;

//     i = 2;
//     here_doc = 0;
//     if (argc < 5)
//         return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
//     if (ft_strncmp(argv[1], "here_doc", 8) == 0)//here_doc
//     {
//         here_doc = 1;
//         i = 3;
//         fileout = ft_open_file(argv[argc -1], 0);//APPEND MODE
//         ft_here_doc(argv[2], argc);
//     }
//     else//multiple cmds
//     {
//         filein = ft_open_file(argv[1], 2);//read input
//         fileout = ft_open_file(argv[argc - 1], 1);//overwrite NOT APPEND
//         dup2(filein,STDIN_FILENO);
//     }
//     while (i < argc -2)
//     {
//         if (pipe(pipe_fd) == -1)
//             return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
//     }
// }


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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/24 13:13:35 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_split(cmd, ' ');//(ex) "ls -l" -> cmd_tab[0] = "ls", cmd_tab[1] = "-l"
	if (!cmd_tab || !cmd_tab[0])
		ft_error_handler(1, cmd_tab, NULL);
	if (ft_strchr(cmd_tab[0], '/'))//check if the given cmd is already with the path
		cmd_path = cmd_tab[0];
	else
		cmd_path = ft_get_path(cmd_tab[0], envp);//(ex) "ls -l" -> find the enviromental path of "ls" -> /bin/ls
	if (!cmd_path)//if there is no path
		ft_error_handler(2, cmd_tab, cmd_path);
	if (execve(cmd_path, cmd_tab, envp) == -1)// execute the command, and if it fails,
		ft_error_handler(3, cmd_tab, cmd_path);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}

void	ft_first_child(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = ft_open_file(argv[1], 0);//open the infile and read
	if (fd < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
	close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
	close(pipe_fd[0]);//close the pipe(read) because we dont need it
	close(pipe_fd[1]);
	ft_exec(argv[2], envp);//execute the first command
}

void	ft_second_child(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = ft_open_file(argv[4], 1);//open the outfile and write, create if it doesnt exist, empty it if it exists already
	if (fd < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);//set argv[4] as the output of the parent process
	close(fd);
	dup2(pipe_fd[0], STDIN_FILENO);//set the pipe(read) as the input of the parent process
	close(pipe_fd[1]);//close the pipe(write) because we dont need it
	close(pipe_fd[0]);
	ft_exec(argv[3], envp);//execute the second command
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_putstr_fd("[Error] Incorrect argument number!\n", 2), 1);
	if (pipe(pipe_fd) == -1)
		return (ft_putstr_fd("[Error] Pipe creation failed!\n", 2), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
	if (pid1 == 0) // First child executes cmd1
		ft_first_child(argv, pipe_fd, envp);
	close(pipe_fd[1]); // Parent closes write end of pipe
	pid2 = fork();
	if (pid2 == -1)
		return (ft_putstr_fd("[Error] Fork failed!\n", 2), 1);
	if (pid2 == 0) // Second child executes cmd2
		ft_second_child(argv, pipe_fd, envp);
	close(pipe_fd[0]); // Parent closes read end of pipe
	waitpid(pid1, &status, 0); // Wait for cmd1
	waitpid(pid2, &status, 0); // Wait for cmd2
	return (WEXITSTATUS(status)); // Return the exit status of cmd2 (last command)
}

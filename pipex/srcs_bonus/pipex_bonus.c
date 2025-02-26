/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/26 11:26:35 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	//printf("Executing: %s (PID: %d)\n", cmd_path, getpid());
	else if (execve(cmd_path, cmd_tab, envp) == -1)// execute the command, and if it fails,
		ft_error_handler(3, cmd_tab, cmd_path);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}

// int	ft_exec(char *cmd, char **envp)
// {
// 	char	**cmd_tab;
// 	char	*cmd_path;

// 	cmd_tab = ft_split(cmd, ' ');//(ex) "ls -l" -> cmd_tab[0] = "ls", cmd_tab[1] = "-l"
// 	if (!cmd_tab || !cmd_tab[0])
// 		return (ft_error_handler(1, cmd_tab, NULL), 0);
// 	if (ft_strchr(cmd_tab[0], '/'))//check if the given cmd is already with the path
// 		cmd_path = cmd_tab[0];
// 	else
// 		cmd_path = ft_get_path(cmd_tab[0], envp);//(ex) "ls -l" -> find the enviromental path of "ls" -> /bin/ls
// 	if (!cmd_path)//if there is no path
// 		return (ft_error_handler(2, cmd_tab, cmd_path), 0);
// 	else if (execve(cmd_path, cmd_tab, envp) == -1)// execute the command, and if it fails,
// 		return (ft_error_handler(3, cmd_tab, cmd_path), 0);
// 	free(cmd_path);
// 	ft_free_tab(cmd_tab);
// 	return (1);
// }

void	ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	fd;

	close(pipe_fd[0]);//close the pipe(read) because we dont need it
	if (here_doc)//here_doc
		dup2(pipe_fd[1], STDOUT_FILENO);//pipe(write) is set as stdout
	else//multiple cmds
	{
		fd = ft_open_file(argv[1], 2, pipe_fd, pid);
		dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
		close(fd);
		dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
	}
	
	close(pipe_fd[1]);
	if (here_doc)
		ft_exec(argv[3], envp);//execute the first command
	else
		ft_exec(argv[2], envp);//execute the first command
}

// void	ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
// {
// 	int	fd;
// 	int exec;

// 	if (here_doc)//here_doc
// 		dup2(pipe_fd[1], STDOUT_FILENO);//pipe(write) is set as stdout
// 	else//multiple cmds
// 	{
// 		fd = ft_open_file(argv[1], 2, pipe_fd, pid);
// 		dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
// 		close(fd);
// 		dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
// 	}
// 	close(pipe_fd[0]);//close the pipe(read) because we dont need it
// 	close(pipe_fd[1]);
// 	if (here_doc)
// 		exec = ft_exec(argv[3], envp);//execute the first command
// 	else
// 		exec = ft_exec(argv[2], envp);//execute the first command
// 	if (!exec)
// 	{
// 		free (pid);
// 		free (pipe_fd);
// 	}
		
// }


void	ft_middle_child(char **argv, int *pipe_fd, char **envp, int i, int num_cmds)
{
	int	j;

	dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO);//calculate the index of the pipe
	dup2(pipe_fd[i * 2  + 1], STDOUT_FILENO);
	j = 0;
	while (j < (2 * (num_cmds - 1)))
	{
		close(pipe_fd[j]);
		j++;
	}
	ft_exec(argv[i + 2], envp);
}

void	ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	fd;
	int	last;
	int	last_pipe_read;
	int	num_cmds;

	last = argc - 1;  // Last argument is always output file
	num_cmds = argc - 3; // Number of commands
	if (here_doc)
		num_cmds = argc - 4; // Adjust for here_doc

	last_pipe_read = pipe_fd[(num_cmds - 2) * 2]; // Get correct last read pipe (if there are 3 cmds, get the )

	// Open output file
	if (!here_doc)
		fd = ft_open_file(argv[last], 1, pipe_fd, pid); // Normal file write
	else
		fd = ft_open_file(argv[last], 0, pipe_fd, pid); // Append mode for here_doc

	// Redirects
	dup2(fd, STDOUT_FILENO);          // Redirect output to outfile
	dup2(last_pipe_read, STDIN_FILENO); // Read input from last pipe

	// Close all pipes before execution
	for (int i = 0; i < (2 * (num_cmds - 1)); i++)
		close(pipe_fd[i]);

	ft_exec(argv[last - 1], envp);     // Execute last command

}


// void	ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
// {
// 	int	fd;
// 	int	last;

// 	last = argc - 1;
// 	if (!here_doc)
// 		fd = ft_open_file(argv[last], 1, pipe_fd, pid);//open the outfile and write, create if it doesnt exist, empty it if it exists already
// 	else
// 		fd = ft_open_file(argv[last], 0, pipe_fd, pid);
// 	dup2(fd, STDOUT_FILENO);//set argv[last] as the output of the process
// 	dup2(pipe_fd[0], STDIN_FILENO);//set the pipe(read) as the input of the process
// 	close(pipe_fd[1]);//close the pipe(write) because we dont need it
// 	ft_exec(argv[last - 1], envp);//execute the second command
// }

void	ft_handle_here_doc_child(int *pipe_fd, char *limiter)
{
	char	*line;

	close(pipe_fd[0]); // Ensure no unnecessary input interference
	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

void	ft_here_doc(int argc, char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 6)
		ft_error_exit("[Error] Incorrect argument number!\n");
	if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
		ft_error_exit("[Error] Pipe/Fork failed!\n");
	if (pid == 0) // Child process
	{
		close(pipe_fd[0]);
		ft_handle_here_doc_child(pipe_fd, limiter);
	}
		
	else // Parent process
	{
		close(pipe_fd[1]); // Close write end
		waitpid(pid, NULL, 0);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]); // Close read end
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		status;
// 	int		here_doc;
// 	int		num_cmds;
// 	int		*pipe_fd;
// 	pid_t	*pid;

// 	here_doc = 0;
// 	num_cmds = argc -3;
// 	if (argc < 5)
// 		return (ft_error_exit("[Error] Incorrect argument number!\n"), 1);
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 	{
// 		ft_here_doc(argc, argv[2]);
// 		here_doc = 1;
// 		num_cmds = 2;
// 	}
// 	pipe_fd = malloc(sizeof(int) * (2 * (num_cmds - 1)));//2 pipes betweeen each cmds
// 	pid = malloc(sizeof(pid_t) *  num_cmds);//forks for each cmds
// 	if (!pipe_fd || !pid)
// 		return (ft_error_exit("[Error] Memory allocation failed!\n"), 1);
// 	ft_create_pipes(pipe_fd, num_cmds);
// 	status = ft_create_process(argc, argv, pipe_fd, envp, here_doc, pid);
// 	ft_close_pipes(pipe_fd, num_cmds);
// 	free(pid);
// 	return (WEXITSTATUS(status));
// }

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		here_doc;
	int		num_cmds;
	int		*pipe_fd;
	pid_t	*pid;

	status = 0;
	here_doc = 0;
	num_cmds = argc -3;
	if (argc < 5)
		return (ft_error_exit("[Error] Incorrect argument number!\n"), 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		ft_here_doc(argc, argv[2]);
		here_doc = 1;
		num_cmds = 2;
	}
	pipe_fd = malloc(sizeof(int) * (2 * (num_cmds - 1)));//2 pipes betweeen each cmds
	pid = malloc(sizeof(pid_t) *  num_cmds);//forks for each cmds
	if (!pipe_fd || !pid)
		return (ft_error_exit("[Error] Memory allocation failed!\n"), 1);
	ft_create_pipes(pipe_fd, num_cmds);
	ft_create_process(argc, argv, pipe_fd, envp, here_doc, pid);
	ft_close_pipes(pipe_fd, num_cmds);
	return (status = ft_wait_children(pid, num_cmds), WEXITSTATUS(status));
}


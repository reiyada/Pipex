/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/26 16:41:41 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_exec(char *cmd, char **envp, pid_t *pid)
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_split(cmd, ' ');//(ex) "ls -l" -> cmd_tab[0] = "ls", cmd_tab[1] = "-l"
	if (!cmd_tab || !cmd_tab[0])
		ft_error_handler(1, cmd_tab, NULL, pid);
	if (ft_strchr(cmd_tab[0], '/'))//check if the given cmd is already with the path
		cmd_path = cmd_tab[0];
	else
		cmd_path = ft_get_path(cmd_tab[0], envp);//(ex) "ls -l" -> find the enviromental path of "ls" -> /bin/ls
	if (!cmd_path)//if there is no path
		ft_error_handler(2, cmd_tab, cmd_path, pid);
	//printf("Executing: %s (PID: %d)\n", cmd_path, getpid());
	if (execve(cmd_path, cmd_tab, envp) == -1)// execute the command, and if it fails,
		ft_error_handler(3, cmd_tab, cmd_path, pid);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}

void	ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	fd;

	close(pipe_fd[0]);
	if (!here_doc)//multiple cmds
	{
		fd = ft_open_file(argv[1], 2, pid);
		dup2(fd, STDIN_FILENO);//set argv[1] as the input of the child process
		close(fd);
		
	}
	dup2(pipe_fd[1], STDOUT_FILENO);//set the pipe(write) as the output of the child process
	close(pipe_fd[1]);
	

	if (here_doc)
		ft_exec(argv[3], envp, pid);//execute the first command
	else
		ft_exec(argv[2], envp, pid);//execute the first command
	
}

void	ft_middle_child(char **argv, int *pipe_fd, char **envp, int i, pid_t *pid)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);//calculate the index of the pipe
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	ft_exec(argv[i + 2], envp, pid);
}

void	ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	fd;

	close(pipe_fd[1]);
	//last_pipe_read = pipe_fd[(num_cmds - 2) * 2]; // Get correct last read pipe (if there are 3 cmds, get the )

	// Open output file
	
	if (!here_doc)
				fd = ft_open_file(argv[argc - 1], 1, pid); // Normal file write
	else
		fd = ft_open_file(argv[argc - 1], 0, pid); // Append mode for here_doc
// Redirects
	
	dup2(fd, STDOUT_FILENO);          // Redirect output to outfile
	close(fd);
	dup2(pipe_fd[0], STDIN_FILENO); // Read input from last pipe
	close(pipe_fd[0]);

	ft_exec(argv[argc - 2], envp, pid);     // Execute last command
	
	

}

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

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		here_doc;
	int		num_cmds;
	int		pipe_fd[2];
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
	pid = malloc(sizeof(pid_t) *  num_cmds);//forks for each cmds
	if (!pid)
		return (free(pid), ft_error_exit("[Error] Memory allocation failed!\n"), 1);
	if (pipe(pipe_fd) == -1)
		return (ft_error_exit("[Error] Pipe creation failed!\n"), 1);
	ft_create_process(argc, argv, pipe_fd, envp, here_doc, pid);
	//ft_close_pipes(pipe_fd, num_cmds);
	return (status = ft_wait_children(pid, num_cmds), WEXITSTATUS(status));
}


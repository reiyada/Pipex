/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:18 by ryada             #+#    #+#             */
/*   Updated: 2025/02/27 22:47:59 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_exec(char *cmd, char **envp, pid_t *pid)
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab || !cmd_tab[0])
		ft_error_handler(1, cmd_tab, NULL, pid);
	if (ft_strchr(cmd_tab[0], '/'))
		cmd_path = cmd_tab[0];
	else
		cmd_path = ft_get_path(cmd_tab[0], envp);
	if (!cmd_path)
		ft_error_handler(2, cmd_tab, cmd_path, pid);
	if (execve(cmd_path, cmd_tab, envp) == -1)
		ft_error_handler(3, cmd_tab, cmd_path, pid);
	free(cmd_path);
	ft_free_tab(cmd_tab);
}

// The key thing to remember is that each process has its own copy of file descriptors
// when it is forked. So, just because the first child closes pipe_fd[1],
// it doesn’t mean that the middle child automatically loses access to pipe_fd[1].
// The parent still holds a copy, and when it forks the middle child, the middle child inherits a copy of pipe_fd[1].

void	ft_first_child(char **argv, int *pipe_fd, char **envp, t_edata edata)
{
	int	fd;

	close(pipe_fd[0]);
	//close(pipe_fd[1]);
	if (!edata.here_doc)
	{
		fd = ft_open_file(argv[1], 2, edata.pid);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (edata.here_doc)
		ft_exec(argv[3], envp, edata.pid);
	else
		ft_exec(argv[2], envp, edata.pid);
}

// void	ft_middle_child(int *pipe_fd, char **envp, t_edata edata)
// {
// 	close(pipe_fd[1]);//close unused write end
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	close(pipe_fd[0]);
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(pipe_fd[1]);
// 	ft_exec(edata.current_cmd, envp, edata.pid);
// }

void	ft_middle_child(int *prev_pipe_fd, int *next_pipe_fd, char **envp, t_edata edata)
{
	close(prev_pipe_fd[1]);
	dup2(prev_pipe_fd[0], STDIN_FILENO);
	close(prev_pipe_fd[0]);
	dup2(next_pipe_fd[1], STDOUT_FILENO);
	close(next_pipe_fd[1]);
	close(next_pipe_fd[0]); 
	ft_exec(edata.current_cmd, envp, edata.pid);
}


void	ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, t_edata edata)
{
	int	fd;

	close(pipe_fd[1]);
	if (!edata.here_doc)
		fd = ft_open_file(argv[argc - 1], 1, edata.pid);
	else
		fd = ft_open_file(argv[argc - 1], 0, edata.pid);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ft_exec(argv[argc - 2], envp, edata.pid);
}

void	ft_handle_here_doc_child(int *pipe_fd, char *limiter)
{
	char	*line;

	close(pipe_fd[0]);
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
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_edata	edata;

	if (argc < 5)
		return (ft_error_exit("[Error] Incorrect argument number!\n"), 1);
	edata = ft_init_edata(argc, argv);
	if (edata.here_doc)
		ft_here_doc(argc, argv[2]);
	edata.pid = malloc(sizeof(pid_t) *  edata.num_cmds);
	if (!edata.pid)
		return (free(edata.pid), ft_error_exit("[Error] Memory allocation failed!\n"), 1);
	ft_create_process(argc, argv, envp, edata);
	ft_wait_children(&edata);
	if (edata.pid != 0)
		free (edata.pid);
	return (edata.status);
}


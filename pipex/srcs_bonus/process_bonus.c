/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/02/24 17:27:15 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_create_pipes(int *pipe_fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_fd + (2 * i)) == -1)//pipe_fd + (2 * i) points the current pipe_fd
			ft_error_exit("[Error] Pipe creation failed!\n");
		i++;
	}
}

void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	i;
	int	num_cmds;
	
	i = 0;
	num_cmds = argc - 3;
	if (here_doc)
		num_cmds = 2;
	while (i < num_cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error_exit("[Error] Fork failed!\n");
		if (pid[i] == 0)
		{
			if (i == 0)
				ft_first_child(argv, pipe_fd, envp, here_doc, pid);
			else if (i == num_cmds - 1)
				ft_last_child(argc, argv, pipe_fd, envp, here_doc, pid);
			else
				ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
		}
		i++;
	}
}

void	ft_close_pipes(int *pipe_fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (num_cmds - 1))//close all the pipes between each cmds
	{
		close (pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	ft_wait_children(pid_t *pid, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}